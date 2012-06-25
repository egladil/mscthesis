//
//  PGFReader.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <gf/PGFReader.h>
#include <gf/stringutil.h>
#include <gf/reader/AbsNameExp.h>
#include <gf/reader/AlternToksSymbol.h>
#include <gf/reader/ApplProduction.h>
#include <gf/reader/AppExp.h>
#include <gf/reader/AppPattern.h>
#include <gf/reader/ArgConstSymbol.h>
#include <gf/reader/CoerceProduction.h>
#include <gf/reader/FloatLit.h>
#include <gf/reader/ImpArgPattern.h>
#include <gf/reader/ImplExp.h>
#include <gf/reader/IntLit.h>
#include <gf/reader/InaccPattern.h>
#include <gf/reader/LambdaExp.h>
#include <gf/reader/LiteralExp.h>
#include <gf/reader/LiteralPattern.h>
#include <gf/reader/MetaExp.h>
#include <gf/reader/StringLit.h>
#include <gf/reader/ToksSymbol.h>
#include <gf/reader/TypedExp.h>
#include <gf/reader/VarExp.h>
#include <gf/reader/VarAsPattern.h>
#include <gf/reader/VarPattern.h>
#include <gf/reader/WildCardPattern.h>

namespace gf {
    
    PGFReader::PGFReader(FILE* inputStream)
        : inputStream(inputStream), readAllLanguages(true) {
    }
    
    PGFReader::PGFReader(FILE* inputStream, const std::set<std::string>& languages)
        : inputStream(inputStream), languages(languages), readAllLanguages(false) {        
    }
    
    PGFReader::~PGFReader() {
    }
    
    void PGFReader::skip(size_t len) throw (gf::IOException) {
        uint8_t buf[1024];
        
        while (len > 0) {
            read(buf, len < sizeof(buf) ? len : sizeof(buf));
            if (len >= sizeof(buf)) {
                len-= sizeof(buf);
            }
        }
    }
    
    void PGFReader::read(uint8_t *buf, size_t len) throw (gf::IOException) {
        size_t count;
        
        count = fread(buf, 1, len, inputStream);
        if (count != len) {
            if (feof(inputStream)) {
                throw IOException("end of file");
            } else if (ferror(inputStream)) {
                throw IOException(errno);
            } else {
                throw IOException("unknown error");
            }
        }
    }
    
    uint8_t PGFReader::readByte() throw (gf::IOException) {
        uint8_t ret;
        
        read(&ret, 1);
        
        return ret;
    }
    
    double PGFReader::readDouble() throw (gf::IOException) {
        double ret;
        
        read((uint8_t*) &ret, sizeof(ret));
        
        return ret;
    }
    
    PGF* PGFReader::readPGF() throw(gf::IOException, gf::UnknownLanguageException) {
        uint8_t version[4];
        std::map<std::string, gf::reader::RLiteral*> flags;
        std::map<std::string, uint32_t> index;
        gf::reader::Abstract* abs;
        std::string startCat;
        int nbConcretes;
        std::vector<gf::reader::Concrete*> concretes;
        
        // Read version
        read(version, sizeof(version));        
#ifdef _DEBUG
        fprintf(stderr, "PGF version: %u.%u.%u.%u\n", version[0], version[1], version[2], version[3]);
#endif
        
        // Read flags
        flags = getListFlag();
        std::map<std::string, gf::reader::RLiteral*>::const_iterator idxFlag = flags.find("index");
        if (idxFlag != flags.end()) {
            gf::reader::StringLit* strlit = dynamic_cast<gf::reader::StringLit*>(idxFlag->second);
            assert(strlit != NULL); // Malformed pgf, throw exception instead.
            index = readIndex(strlit->getValue());
#ifdef _DEBUG
            fprintf(stderr, "[");
            for (std::map<std::string, uint32_t>::const_iterator it = index.begin(); it != index.end(); it++) {
                fprintf(stderr, "%s[%s, %u]", it == index.begin() ? "" : ", ", it->first.c_str(), it->second);
            }
            fprintf(stderr, "]\n");
#endif
        }
        
        // Read abstact grammar
        abs = getAbstract();
        startCat = abs->startcat();
        
        // Read concrete grammars
        nbConcretes = getInt();
        for (int i = 0; i < nbConcretes; i++) {
            std::string name;
            
            name = getIdent();
#ifdef _DEBUG
            fprintf(stderr, "Language: %s\n", name.c_str());
#endif
            if (readAllLanguages || languages.erase(name) > 0) {
                concretes.push_back(getConcrete(name, startCat));
            } else if (!index.empty()) {
                std::map<std::string, uint32_t>::const_iterator langIdx = index.find(name);
                assert(langIdx != index.end()); // Malformed pgf, throw exception instead.
                skip(langIdx->second);
#ifdef _DEBUG
                fprintf(stderr, "Skipping %s\n", name.c_str());
#endif
            } else {
                // Skip manually
                getConcrete(name, startCat);
            }
        }
            
        // Was all languages found?
        if (!languages.empty()) {
            throw UnknownLanguageException(*languages.begin());
        }
        
        return new PGF(makeInt16(version[0], version[1]), makeInt16(version[2], version[3]), flags, abs, concretes);
    }
    
    std::string PGFReader::getStartCat(const std::map<std::string, gf::reader::RLiteral*> &flags) const {
        std::map<std::string, gf::reader::RLiteral*>::const_iterator it = flags.find("startcat");
        gf::reader::StringLit* strlit;
        
        if (it == flags.end()) {
            return "Sentence";
        }
        
        strlit = dynamic_cast<gf::reader::StringLit*>(it->second);
        assert(strlit != NULL); // Malformed pgf, throw exception instead.
        return strlit->getValue();
    }
    
    std::map<std::string, uint32_t> PGFReader::readIndex(const std::string &s) const {
        std::vector<std::string> items;
        std::map<std::string, uint32_t> ret;
        
        items = split(s, ' ');
        for (std::vector<std::string>::const_iterator it = items.begin(); it != items.end(); it++) {
            std::string str;
            std::vector<std::string> idx;
            
            str = trim(*it);
            if (str.empty()) {
                continue;
            }
            
            idx = split(str, ':');
            assert(idx.size() == 2); // Malformed pgf, throw exception instead.
            
            ret.insert(std::make_pair(idx.front(), strtoul(idx.back().c_str(), NULL, 10)));
        }
        
        return ret;
    }
    
    gf::reader::Abstract* PGFReader::getAbstract() throw(gf::IOException) {
        std::string name;
        std::map<std::string, gf::reader::RLiteral*> flags;
        std::vector<gf::reader::AbsFun*> absFuns;
        std::vector<gf::reader::AbsCat*> absCats;
        
        name = getIdent();
#ifdef _DEBUG
        fprintf(stderr, "Abstract syntax [%s]\n", name.c_str());
#endif
        flags = getListFlag();
        absFuns = getListAbsFun();
        absCats = getListAbsCat();
        
        return new gf::reader::Abstract(name, flags, absFuns, absCats);
    }
    
    std::vector<gf::reader::Pattern*> PGFReader::getListPattern() throw(gf::IOException) {
        int cnt;
        std::vector<gf::reader::Pattern*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getPattern());
        }
        
        return ret;
    }
    
    gf::reader::Eq* PGFReader::getEq() throw(gf::IOException) {
        std::vector<gf::reader::Pattern*> patterns;
        gf::reader::Expr* expr;
        
        patterns = getListPattern();
        expr = getExpr();
        
        return new gf::reader::Eq(patterns, expr);
    }
    
    gf::reader::AbsFun* PGFReader::getAbsFun() throw(gf::IOException) {
        std::string name;
        gf::reader::Type* type;
        int32_t arity;
        uint8_t hasEquations;
        std::vector<gf::reader::Eq*> equations;
        double weight;
        gf::reader::AbsFun* ret;
        
        name = getIdent();
#ifdef _DEBUG
        fprintf(stderr, "AbsFun: '%s'\n", name.c_str());
#endif
        type = getType();
        arity = getInt();
        hasEquations = readByte();
        if (hasEquations != 0) {
            equations = getListEq();
        }
        weight = readDouble();
        
        ret = new gf::reader::AbsFun(name, type, arity, equations, weight);
        
#ifdef _DEBUG
        fprintf(stderr, "/AbsFun: %s\n", ret->toString().c_str());
#endif
        
        return ret;
    }
    
    gf::reader::AbsCat* PGFReader::getAbsCat() throw(gf::IOException) {
        std::string name;
        std::vector<gf::reader::Hypo*> hypos;
        std::vector<gf::reader::WeightedIdent*> functions;
        
        name = getIdent();
        hypos = getListHypo();
        functions = getListWeightedIdent();
        
        return new gf::reader::AbsCat(name, hypos, functions);
    }
    
    std::vector<gf::reader::AbsFun*> PGFReader::getListAbsFun() throw(gf::IOException) {
        int cnt;
        std::vector<gf::reader::AbsFun*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getAbsFun());
        }
        
        return ret;
    }
    
    std::vector<gf::reader::AbsCat*> PGFReader::getListAbsCat() throw(gf::IOException) {
        int cnt;
        std::vector<gf::reader::AbsCat*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getAbsCat());
        }
        
        return ret;
    }
    
    gf::reader::Type* PGFReader::getType() throw(gf::IOException) {
        std::vector<gf::reader::Hypo*> hypos;
        std::string returnCat;
        std::vector<gf::reader::Expr*> expressions;
        gf::reader::Type* ret;
        
        hypos = getListHypo();
        returnCat = getIdent();
        expressions = getListExpr();
        
        ret = new gf::reader::Type(hypos, returnCat, expressions);
#ifdef _DEBUG
        fprintf(stderr, "Type: %s\n", ret.toString().c_str());
#endif
        return ret;
    }
    
    gf::reader::Hypo* PGFReader::getHypo() throw(gf::IOException) {
        uint8_t btype;
        std::string varName;
        gf::reader::Type* type;
        
        btype = readByte();
        varName = getIdent();
        type = getType();
        
        return new gf::reader::Hypo(btype != 0, varName, type);
    }
    
    std::vector<gf::reader::Hypo*> PGFReader::getListHypo() throw(gf::IOException) {
        int cnt;
        std::vector<gf::reader::Hypo*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getHypo());
        }
        
        return ret;
    }
    
    std::vector<gf::reader::Expr*> PGFReader::getListExpr() throw(gf::IOException) {
        int cnt;
        std::vector<gf::reader::Expr*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getExpr());
        }
        
        return ret;
    }
    
    gf::reader::Expr* PGFReader::getExpr() throw(gf::IOException) {
        int tag;
        
        tag = getInt();
        switch (tag) {
            case 0: /* lambda abstraction */ {
                uint8_t boundType;
                std::string variableName;
                gf::reader::Expr* expr;
                
                boundType = readByte();
                variableName = getIdent();
                expr = getExpr();
                return new gf::reader::LambdaExp(boundType != 0, variableName, expr);
            }
            case 1: /* expression application */ {
                gf::reader::Expr* expr1;
                gf::reader::Expr* expr2;
                
                expr1 = getExpr();
                expr2 = getExpr();
                
                return new gf::reader::AppExp(expr1, expr2);
            }
            case 2: /* literal expression */ {
                gf::reader::RLiteral* literal;
                
                literal = getLiteral();
                
                return new gf::reader::LiteralExp(literal);
            }
            case 3: /* meta variable */ {
                int id;
                
                id = getInt();
                
                return new gf::reader::MetaExp(id);
            }
            case 4: /* abstract function name */ {
                std::string absFun;
                
                absFun = getIdent();
                
                return new gf::reader::AbsNameExp(absFun);
            }
            case 5: /* variable */ {
                int var;
                
                var = getInt();
                
                return new gf::reader::VarExp(var);
            }
            case 6: /* type annotated expression */ {
                gf::reader::Expr* expr;
                gf::reader::Type* type;
                
                expr = getExpr();
                type = getType();
                
                return new gf::reader::TypedExp(expr, type);
            }
            case 7: {
                gf::reader::Expr* expr;
                
                expr = getExpr();
                
                return new gf::reader::ImplExp(expr);
            }
        }
        
        throw IOException("invalid tag for expression: " + toString(tag));
    }
    
    std::vector<gf::reader::Eq*> PGFReader::getListEq() throw (gf::IOException) {
        int cnt;
        std::vector<gf::reader::Eq*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getEq());
        }
        
        return ret;        
    }

    gf::reader::Pattern* PGFReader::getPattern() throw (gf::IOException) {
        int tag;
        
        tag = getInt();
        switch (tag) {
            case 0: /* application pattern */ {
                std::string absFun;
                std::vector<gf::reader::Pattern*> patterns;
                
                absFun = getIdent();
                patterns = getListPattern();
                
                return new gf::reader::AppPattern(absFun, patterns);
            }
            case 1: /* variable pattern */ {
                std::string variableName;
                
                variableName = getIdent();
                
                return new gf::reader::VarPattern(variableName);
            }
            case 2: /* variable as pattern */ {
                std::string name;
                gf::reader::Pattern* pattern;
                
                name = getIdent();
                pattern = getPattern();
                
                return new gf::reader::VarAsPattern(name, pattern);
            }
            case 3: /* wildcard pattern */ {
                return new gf::reader::WildCardPattern();
            }
            case 4: /* literal pattern */ {
                gf::reader::RLiteral* literal;
                
                literal = getLiteral();
                
                return new gf::reader::LiteralPattern(literal);
            }
            case 5: /* implicit argument */{
                gf::reader::Pattern* pattern;
                
                pattern = getPattern();
                
                return new gf::reader::ImpArgPattern(pattern);
            }
            case 6: /* inaccessible pattern */ {
                gf::reader::Expr* expr;
                
                expr = getExpr();
                
                return new gf::reader::InaccPattern(expr);
            }
        }
        
        throw IOException("invalid tag for pattern: " + toString(tag));
    }
    
    gf::reader::RLiteral* PGFReader::getLiteral() throw (gf::IOException) {
        int tag;
        
        tag = getInt();
        switch (tag) {
            case 0: /* string literal */ {
                std::string str;
                
                str = getString();
                
                return new gf::reader::StringLit(str);
            }
            case 1: /* integer literal */ {
                int32_t i;
                
                i = getInt();
                
                return new gf::reader::IntLit(i);
                
            }
            case 2: {
                double d;
                
                d = readDouble();
                
                return new gf::reader::FloatLit(d);
            }
        }
        
        throw IOException("invalid tag for literal: " + toString(tag));
    }
    
    
    gf::reader::Concrete* PGFReader::getConcrete(const std::string &name, const std::string &startCat) throw (gf::IOException) {
        std::map<std::string, gf::reader::RLiteral*> flags;
        std::vector<gf::reader::Sequence*> sequences;
        std::vector<gf::reader::CncFun*> cncFuns;
        std::vector<gf::reader::ProductionSet*> productionSets;
        std::map<std::string, gf::reader::CncCat*> cncCats;
        int32_t fId;
        
#ifdef _DEBUG
        fprintf(stderr, "Concrete: %s\n", name.c_str());
        
        fprintf(stderr, "Concrete: Reading flags\n");
#endif
        flags = getListFlag();
        
#ifdef _DEBUG
        fprintf(stderr, "Concrete: Skipping print names\n");
#endif
        skipListPrintName();
        
#ifdef _DEBUG
        fprintf(stderr, "Concrete: Reading sequences\n");
#endif
        sequences = getListSequence();
        cncFuns = getListCncFun(sequences);
        productionSets = getListProductionSet(cncFuns);
        
        cncCats = getListCncCat();
        fId = getInt();
        
        return new gf::reader::Concrete(name, flags, sequences, cncFuns, productionSets, cncCats, fId, startCat);
    }
    
    void PGFReader::skipPrintName() throw (gf::IOException) {
        getIdent();
        getString();
    }
    
    void PGFReader::skipListPrintName() throw (gf::IOException) {
        int cnt;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            skipPrintName();
        }
    }
    
    gf::reader::Sequence* PGFReader::getSequence() throw (gf::IOException) {
        std::vector<gf::reader::Symbol*> symbols;
        
        symbols = getListSymbol();
        
        return new gf::reader::Sequence(symbols);
    }
    
    std::vector<gf::reader::Sequence*> PGFReader::getListSequence() throw (gf::IOException) {
        int cnt;
        std::vector<gf::reader::Sequence*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getSequence());
        }
        
        return ret;
    }
    
    gf::reader::Symbol* PGFReader::getSymbol() throw (gf::IOException) {
        int tag;
        gf::reader::Symbol* ret;
        
        tag = getInt();  
#ifdef _DEBUG
        fprintf(stderr, "Symbol: type=%i\n", tag);
#endif
        switch (tag) {
            case 0: /* category (non-terminal symbol) */
            case 1: /* literal (not implemented properly) */ {
                int32_t arg;
                int32_t cons;
                
                arg = getInt();
                cons = getInt();
                
                ret = new gf::reader::ArgConstSymbol(arg, cons);
                break;
            }
            case 2: /* variable */ {
                throw IOException("variable symbol not implemented");
            }
            case 3: /* sequence of tokens */ {
                std::vector<std::string> strings;
                
                strings = getListString();
                
                ret = new gf::reader::ToksSymbol(strings);
                break;
            }
            case 4: /* alternative tokens */ {
                std::vector<std::string> strings;
                std::vector<gf::reader::Alternative*> alternatives;
                
                strings = getListString();
                alternatives = getListAlternative();
                
                ret = new gf::reader::AlternToksSymbol(strings, alternatives);
                break;
            }
            default:
                throw IOException("invalid tag for symbol: " + toString(tag));
        }
        
#ifdef _DEBUG
        fprintf(stderr, "/Symbol: %s\n", ret->toString().c_str());
#endif
        
        return ret;
    }
    
    std::vector<gf::reader::Alternative*> PGFReader::getListAlternative() throw (gf::IOException) {
        int cnt;
        std::vector<gf::reader::Alternative*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getAlternative());
        }
        
        return ret;
    }
    
    gf::reader::Alternative* PGFReader::getAlternative() throw (gf::IOException) {
        std::vector<std::string> tokens;
        std::vector<std::string> prefixes;
        
        return new gf::reader::Alternative(tokens, prefixes);
    }
    
    std::vector<gf::reader::Symbol*> PGFReader::getListSymbol() throw (gf::IOException) {
        int cnt;
        std::vector<gf::reader::Symbol*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getSymbol());
        }
        
        return ret;
    }
    
    gf::reader::CncFun* PGFReader::getCncFun(const std::vector<gf::reader::Sequence*> &sequences) throw (gf::IOException) {
        std::string name;
        std::vector<uint32_t> indices;
        std::vector<gf::reader::Sequence*> newSequences;
        
        name = getIdent();
        indices = getListInt();
        for (std::vector<uint32_t>::const_iterator it = indices.begin(); it != indices.end(); it++) {
            uint32_t idx;
            gf::reader::Sequence* sequence;
            
            idx = *it;
            if (idx >= sequences.size()) {
                throw IOException("error in pgf file: sequence index out of bounds");
            }
            
            sequence = sequences.at(idx);
            // sequence->addReference();
            newSequences.push_back(sequence);
        }
        
        return new gf::reader::CncFun(name, newSequences);
    }
    
    std::vector<gf::reader::CncFun*> PGFReader::getListCncFun(const std::vector<gf::reader::Sequence *> &sequences) throw (gf::IOException) {
        int cnt;
        std::vector<gf::reader::CncFun*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getCncFun(sequences));
        }
        
        return ret;
    }
    
    void PGFReader::skipListLinDef() throw (gf::IOException) {
        int cnt;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            skipLinDef();
        }
    }
    
    void PGFReader::skipLinDef() throw (gf::IOException) {
        int cnt;
        
        getInt(); // key
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            getInt(); // fun id
        }
    }
    
    gf::reader::ProductionSet* PGFReader::getProductionSet(const std::vector<gf::reader::CncFun *> &cncFuns) throw (gf::IOException) {
        uint32_t id;
        std::vector<gf::reader::Production*> productions;
        
        id = getInt();
        productions = getListProduction(id, cncFuns);
        
        return new gf::reader::ProductionSet(id, productions);
    }
    
    std::vector<gf::reader::ProductionSet*> PGFReader::getListProductionSet(const std::vector<gf::reader::CncFun *> &cncFuns) throw (gf::IOException) {
        int cnt;
        std::vector<gf::reader::ProductionSet*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getProductionSet(cncFuns));
        }
        
        return ret;        
    }
    
    std::vector<gf::reader::Production*> PGFReader::getListProduction(uint32_t leftCat, const std::vector<gf::reader::CncFun *> &cncFuns) throw (gf::IOException) {
        int cnt;
        std::vector<gf::reader::Production*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getProduction(leftCat, cncFuns));
        }
        
        return ret;        
    }
    
    gf::reader::Production* PGFReader::getProduction(int32_t leftCat, const std::vector<gf::reader::CncFun *> &cncFuns) throw (gf::IOException) {
        int tag;
        gf::reader::Production* ret = NULL;
        
        tag = getInt();
#ifdef _DEBUG
        fprintf(stderr, "Production: type=%i\n", tag);
#endif
        switch (tag) {
            case 0: /* application */ {
                uint32_t funId;
                std::vector<uint32_t> domain;
                gf::reader::CncFun* cncFun;
                
                funId = getInt();
                domain = getDomainFromPArgs();
                
                if (funId >= cncFuns.size()) {
                    throw IOException("error in pgf file: concrete function index out of bounds");
                }
                cncFun = cncFuns.at(funId);
                // cncFun->addRef();
                
                ret = new gf::reader::ApplProduction(leftCat, cncFun, domain);
                break;
            }
            case 1: /* coercion */ {
                uint32_t id;
                
                id = getInt();
                
                ret = new gf::reader::CoerceProduction(leftCat, id);
                break;
            }
            default:
                throw IOException("invalid tag for production: " + toString(tag));
        }
        
#ifdef _DEBUG
        fprintf(stderr, "/Production: %s\n", ret.toString().c_str());
#endif
        return ret;
    }
    
    std::vector<uint32_t> PGFReader::getDomainFromPArgs() throw (gf::IOException) {
        int cnt;
        std::vector<uint32_t> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            getListInt(); // Skip
            ret.push_back(getInt());
        }
        
        return ret;
    }
    
    gf::reader::CncCat* PGFReader::getCncCat() throw (gf::IOException) {
        std::string name;
        uint32_t firstId;
        uint32_t lastId;
        std::vector<std::string> labels;
        
        name = getIdent();
        firstId = getInt();
        lastId = getInt();
        labels = getListString();
        
        return new gf::reader::CncCat(name, firstId, lastId, labels);
    }
    
    std::map<std::string, gf::reader::CncCat*> PGFReader::getListCncCat() throw (gf::IOException) {
        int cnt;
        std::map<std::string, gf::reader::CncCat*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            gf::reader::CncCat* cat;
            
            cat = getCncCat();
            
            ret.insert(std::make_pair(cat->getName(), cat));
        }
        
        return ret;          
    }
    
    std::map<std::string, gf::reader::RLiteral*> PGFReader::getListFlag() throw (gf::IOException) {
        int cnt;
        std::map<std::string, gf::reader::RLiteral*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            std::string name;
            gf::reader::RLiteral* literal;
            
            name = getIdent();
            literal = getLiteral();
            
            ret.insert(std::make_pair(name, literal));
        }
        
        return ret; 
    }
    
    std::string PGFReader::getString() throw (gf::IOException) {
        int cnt;
        std::string ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            uint8_t r;
            
            r = readByte();
            ret+= r;
            if (r >= 0xC0 && r <= 0xDF) {
                ret+= readByte();
            } else if (r >= 0xE0 && r <= 0xEF) {
                ret+= readByte();
                ret+= readByte();
            } else if (r >= 0xF0 && r <= 0xF4) {
                ret+= readByte();
                ret+= readByte();
                ret+= readByte();
            } else if (r >= 0xF8 && r <= 0xFB) {
                ret+= readByte();
                ret+= readByte();
                ret+= readByte();
                ret+= readByte();
            } else if (r >= 0xFC && r <= 0xFD) {
                ret+= readByte();
                ret+= readByte();
                ret+= readByte();
                ret+= readByte();
                ret+= readByte();
            } else {
                throw IOException("unsupported/undefined utf8 sequence start: " + toString(r));
            }
        }
        
        return ret;
    }
    
    std::vector<std::string> PGFReader::getListString() throw (gf::IOException) {
        int cnt;
        std::vector<std::string> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getString());
        }
        
        return ret; 
    }
    
    std::string PGFReader::getIdent() throw (gf::IOException) {
        int cnt;
        
        cnt = getInt();
        if (cnt == 0) {
            return "";
        }
        
        char buf[cnt + 1];
        read((uint8_t*) buf, cnt);
        buf[cnt] = 0;
        
        return convIso88591toUtf8(buf);
    }
    
    std::vector<std::string> PGFReader::getListIdent() throw (gf::IOException) {
        int cnt;
        std::vector<std::string> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getIdent());
        }
        
        return ret; 
    }
    
    std::vector<gf::reader::WeightedIdent*> PGFReader::getListWeightedIdent() throw (gf::IOException) {
        int cnt;
        std::vector<gf::reader::WeightedIdent*> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            double weight;
            std::string ident;
            
            weight = readDouble();
            ident = getIdent();
            
            ret.push_back(new gf::reader::WeightedIdent(ident, weight));
        }
        
        return ret;
    }
    
    uint32_t PGFReader::getInt() throw (gf::IOException) {
        uint32_t ret;
        uint32_t tmp;
        
        ret = readByte();
        if (ret <= 0x7f) {
            return ret;
        }
        
        ret&= 0x7f;
        
        tmp = getInt();
        ret|= tmp << 7;
        
        return ret;
    }
    
    std::vector<uint32_t> PGFReader::getListInt() throw (gf::IOException) {
        int cnt;
        std::vector<uint32_t> ret;
        
        cnt = getInt();
        for (int i = 0; i < cnt; i++) {
            ret.push_back(getInt());
        }
        
        return ret; 
    }
    
}
