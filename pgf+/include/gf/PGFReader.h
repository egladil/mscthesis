//
//  PGFReader.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__PGFReader_h
#define pgf__PGFReader_h

#include <stdio.h>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <gf/IOException.h>
#include <gf/PGF.h>
#include <gf/UnknownLanguageException.h>
#include <gf/reader/AbsCat.h>
#include <gf/reader/AbsFun.h>
#include <gf/reader/Abstract.h>
#include <gf/reader/Alternative.h>
#include <gf/reader/CncCat.h>
#include <gf/reader/CncFun.h>
#include <gf/reader/Concrete.h>
#include <gf/reader/Eq.h>
#include <gf/reader/Expr.h>
#include <gf/reader/Hypo.h>
#include <gf/reader/Pattern.h>
#include <gf/reader/Production.h>
#include <gf/reader/ProductionSet.h>
#include <gf/reader/RLiteral.h>
#include <gf/reader/Sequence.h>
#include <gf/reader/Symbol.h>
#include <gf/reader/Type.h>
#include <gf/reader/WeightedIdent.h>

namespace gf {
    
    class PGFReader {
    private:
        FILE* inputStream;
        std::set<std::string> languages;
        bool readAllLanguages;
        
        /**
         * Skip some bytes.
         * @param len the number of bytes to skip.
         * @throws gf::IOException if the specified number of bytes could not be skipped for some reason.
         */
        void skip(size_t len) throw(gf::IOException);
        
        /**
         * Read bytes into a buffer.
         * @param buf the buffer to store the data in.
         * @param len the number of bytes to read.
         * @throws gf::IOException if the specified number of bytes could not be read for some reason.
         */
        void read(uint8_t* buf, size_t len) throw(gf::IOException);
        
        /**
         * Read one byte.
         * @return the byte read.
         * @throws gf::IOException if there was a read error or if the end of file was encountered
         */
        uint8_t readByte() throw(gf::IOException);
        
        /**
         * Read one double.
         * @return the double read.
         * @throws gf::IOException if there was a read error or if the end of file was encountered
         */
        double readDouble() throw(gf::IOException);

        /**
         * This function guess the default start category from the
         * PGF flags: if the startcat flag is set then it is taken as default cat.
         * otherwise "Sentence" is taken as default category.
         * @param the flags for the grammar
         * @return the start category.
         */
        std::string getStartCat(const std::map<std::string, gf::reader::RLiteral*>& flags) const;
        
        std::map<std::string, uint32_t> readIndex(const std::string& s) const;
        
        /**
         * This function reads the part of the pgf binary corresponding to
         * the abstract grammar.
         * @return the abstract grammar read.
         * @throws gf::IOException if there was a read error
         */
        gf::reader::Abstract* getAbstract() throw(gf::IOException);

        /**
         * @throws gf::IOException if there was a read error
         */
        std::vector<gf::reader::Pattern*> getListPattern() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        gf::reader::Eq* getEq() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        gf::reader::AbsFun* getAbsFun() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        gf::reader::AbsCat* getAbsCat() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::vector<gf::reader::AbsFun*> getListAbsFun() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::vector<gf::reader::AbsCat*> getListAbsCat() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        gf::reader::Type* getType() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        gf::reader::Hypo* getHypo() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::vector<gf::reader::Hypo*> getListHypo() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::vector<gf::reader::Expr*> getListExpr() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        gf::reader::Expr* getExpr() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::vector<gf::reader::Eq*> getListEq() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        gf::reader::Pattern* getPattern() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        gf::reader::RLiteral* getLiteral() throw(gf::IOException);
        
        
        /**
         * This function reads a part of the pgf binary corresponding to
         * a concrete grammar.
         * @param name the name of the concrete grammar.
         * @param startCat the name of the starting category.
         * @return the concrete grammar read.
         * @throws gf::IOException if there was a read error
         */
        gf::reader::Concrete* getConcrete(const std::string& name, const std::string& startCat) throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        void skipPrintName() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        void skipListPrintName() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        gf::reader::Sequence* getSequence() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::vector<gf::reader::Sequence*> getListSequence() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        gf::reader::Symbol* getSymbol() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::vector<gf::reader::Alternative> getListAlternative() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        gf::reader::Alternative getAlternative() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::vector<gf::reader::Symbol*> getListSymbol() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        gf::reader::CncFun* getCncFun(const std::vector<gf::reader::Sequence>& sequences) throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::vector<gf::reader::CncFun*> getListCncFun(const std::vector<gf::reader::Sequence>& sequences) throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        void skipListLinDef() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        void skipLinDef() throw(gf::IOException);
        
        /**
         * Read a production set.
         * @param cncFuns the list of concrete functions.
         * @return the ProductionSet read.
         * @throws gf::IOException if there was a read error
         */
        gf::reader::ProductionSet* getProductionSet(const std::vector<gf::reader::CncFun*>& cncFuns) throw(gf::IOException);
        
        /**
         * Read a list of production sets.
         * @param cncFuns the list of concrete functions.
         * @return the list of ProductionSets read.
         * @throws gf::IOException if there was a read error
         */
        std::vector<gf::reader::ProductionSet*> getListProductionSet(const std::vector<gf::reader::CncFun*>& cncFuns) throw(gf::IOException);
        
        /**
         * Read a production.
         * @param leftCat is the left hand side category of this production
         *                (read only once for the whole production set)
         * @param cncFuns is the list of concrete function, used here to set the
         *                function of the production (only given by its index in
         *                the list)
         * @return the Production read.
         * @throws gf::IOException if there was a read error
         */
        gf::reader::Production* getProduction(int32_t leftCat, const std::vector<gf::reader::CncFun*>& cncFuns) throw(gf::IOException);
        
        /**
         * Read a list of PArgs and return a list of their domains.
         * @return the domains for the PArgs read.
         * @throws gf::IOException if there was a read error
         */
        std::vector<int32_t> getDomainFromPArgs() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        gf::reader::CncCat* getCncCat() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::map<std::string, gf::reader::CncCat*> getListCncCat() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::map<std::string, gf::reader::RLiteral*> getListFlag() throw(gf::IOException);
        
        /**
         * Read an utf8 encoded string.
         * @return an utf8 encoded string.
         * @throws gf::IOException if there was a read error
         */
        std::string getString() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::vector<std::string> getListString() throw(gf::IOException);
        
        /**
         * Read a iso-8859-1 (latin1) encoded string and convert it to utf8.
         * @return an utf8 encoded string.
         * @throws gf::IOException if there was a read error
         */
        std::string getIdent() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::vector<std::string> getListIdent() throw(gf::IOException);
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::vector<gf::reader::WeightedIdent*> getListWeightedIdent() throw(gf::IOException);
        
        /**
         * Read an integer encoded by the pgf serialiser.
         * @return the integer read.
         * @throws gf::IOException if there was a read error
         */
        int32_t getInt();
        
        /**
         * @throws gf::IOException if there was a read error
         */
        std::vector<int32_t> getListInt() throw(gf::IOException);
        
        /**
         * Combine two bytes into a 16 bit integer.
         * @param j1 the least significant byte.
         * @param j2 the most significant byte.
         * @return a 16 bit integer.
         */
        uint16_t makeInt16(uint8_t j1, uint8_t j2);
        
        
    public:
        PGFReader(FILE* inputStream);
        PGFReader(FILE* inputStream, const std::set<std::string>& languages);
        virtual ~PGFReader();
        
        /**
         * Read a pgf file from this PGFReader.
         * @return a pointer to the newly created pgf file
         * @throws gf::IOException if there was a problem reading from the input stream
         * @throws gf::UnknownLanguageException if any of the specified languages were not found
         */
        virtual PGF* readPGF() throw(gf::IOException, gf::UnknownLanguageException);
    };
    
}

#endif
