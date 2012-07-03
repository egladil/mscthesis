//
//  Linearizer.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-29.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <assert.h>

#include <gf/stringutil.h>
#include <gf/Linearizer.h>
#include <gf/linearizer/Bracket.h>
#include <gf/linearizer/LeafKP.h>
#include <gf/linearizer/LeafKS.h>
#include <gf/reader/Alternative.h>
#include <gf/reader/AlternToksSymbol.h>
#include <gf/reader/ApplProduction.h>
#include <gf/reader/ArgConstSymbol.h>
#include <gf/reader/CoerceProduction.h>
#include <gf/reader/ToksSymbol.h>
#include <gf/trees/Printer.H>

namespace gf {
    
    Linearizer::Linearizer(PGF* pgf, gf::reader::Concrete* concrete) throw (gf::LinearizerException)
        : pgf(pgf), concrete(concrete) {
        this->lProductions = getLProductions();
    }
    
    Linearizer::Linearizer(PGF* pgf, const std::string& concrete) throw (gf::LinearizerException)
        : pgf(pgf), concrete(pgf->getConcrete(concrete)) {
        this->concrete->addReference();
        this->lProductions = getLProductions();
    }
    
    Linearizer::~Linearizer() {
        gf::release(pgf);
        gf::release(concrete);
        // TODO: Release lProductions?
    }
    
    std::vector<std::string> Linearizer::linearizeTokens(const Tree* absyn) const throw (gf::LinearizerException) {
        std::vector<gf::linearizer::LinTriple*> lin;
        std::vector<std::string> ret;
        
        lin = linearize(absyn);        
        if (lin.empty()) {
            throw LinearizerException("no linearization");
        }
        
        ret = renderLin(lin.front());
        
        for (std::vector<gf::linearizer::LinTriple*>::iterator it = lin.begin(); it != lin.end(); it++) {
            gf::release(*it);
        }
        
        return ret;
    }
    
    std::string Linearizer::linearizeString(const Tree* absyn) const throw (gf::LinearizerException) {
        return merge(linearizeTokens(absyn), " ");
    }
    
    Linearizer::MapStrMapIntSP Linearizer::getLProductions() const throw (gf::LinearizerException) {
        MapIntSP empty;
        MapIntSP productions;
        MapStrMapIntSP ret;
        
        productions = filterProductions(empty, concrete->getSetOfProductions());
        ret = linIndex(productions);
        
        // TODO: Release productions?
        
        return ret;
    }
    
    Linearizer::MapStrMapIntSP Linearizer::linIndex(const MapIntSP& productions) const {
        MapStrMapIntSP ret;
        
        for (MapIntSP::const_iterator outer = productions.begin(); outer != productions.end(); outer++) {
            uint32_t res = outer->first;
            
            for (SetProd::const_iterator prod = outer->second.begin(); prod != outer->second.end(); prod++) {
                std::vector<std::string> funs;
                
                funs = getFunctions(*prod, productions);
                
                for (std::vector<std::string>::const_iterator inner = funs.begin(); inner != funs.end(); inner++) {
                    std::string newLin = *inner;
                    
                    MapStrMapIntSP::iterator oldMap = ret.find(newLin);
                    if (oldMap != ret.end()) {
                        MapIntSP::iterator oldSet = oldMap->second.find(res);
                        if (oldSet != oldMap->second.end()) {
                            oldSet->second.insert(*prod);
                        } else {
                            SetProd prodSet;
                            
                            prodSet.insert(*prod);
                            
                            oldMap->second.insert(std::make_pair(res, prodSet));
                        }
                    } else {
                        SetProd prodSet;
                        MapIntSP newMap;
                        
                        prodSet.insert(*prod);
                        newMap.insert(std::make_pair(res, prodSet));
                        
                        ret.insert(std::make_pair(newLin, newMap));
                    }
                }
            }
            
        }
        
        return ret;
    }
    
    std::vector<std::string> Linearizer::getFunctions(gf::reader::Production* production, const MapIntSP& productions) const {
        std::vector<std::string> ret;
        gf::reader::ApplProduction* appl;
        gf::reader::CoerceProduction* coerce;
        
        appl = dynamic_cast<gf::reader::ApplProduction*>(production);
        coerce = dynamic_cast<gf::reader::CoerceProduction*>(production);
        if (appl != NULL) {
            ret.push_back(appl->getFunction()->getName());
        } else if (coerce != NULL) {
            uint32_t fid;
            
            fid = coerce->getInitId();
            MapIntSP::const_iterator it = productions.find(fid);
            if (it != productions.end()) {
                for (SetProd::const_iterator prod = it->second.begin(); prod != it->second.end(); prod++) {
                    std::vector<std::string> funs;
                    
                    funs = getFunctions(*prod, productions);
                    ret.insert(ret.end(), funs.begin(), funs.end());
                }
            }
        } else {
            assert(0);
        }
        
        return ret;
    }
    
    bool Linearizer::conditionProd(uint32_t index, const MapIntSP& productions) const {
        if (isLiteral(index)) {
            return true;
        }
        
        return productions.find(index) != productions.end();
    }
    
    Linearizer::SetProd Linearizer::filterProdSet1(const MapIntSP& productions, const SetProd& set) const {
        SetProd ret;
        
        for (SetProd::const_iterator it = set.begin(); it != set.end(); it++) {
            if (filterRule(productions, *it)) {
                ret.insert(*it);
            }
        }
        
        return ret;
    }
    
    Linearizer::MapIntSP Linearizer::filterProductions(const MapIntSP& productions0, const MapIntSP& productions) const {
        MapIntSP filteredProductions;
        MapIntSP productions1;
        bool modified;
        
        for (MapIntSP::const_iterator it = productions.begin(); it != productions.end(); it++) {
            SetProd set;
            
            set = filterProdSet1(productions0, it->second);
            if (!set.empty()) {
                filteredProductions.insert(std::make_pair(it->first, set));
            }
        }
        
        productions1 = productions0;
        modified = false;
        for (MapIntSP::const_iterator it = filteredProductions.begin(); it != filteredProductions.end(); it++) {
            uint32_t index = it->first;
            SetProd set = it->second;
            
            MapIntSP::const_iterator old = productions0.find(index);
            if (old != productions0.end()) {
                if (old->second != set) {
                    set.insert(old->second.begin(), old->second.end());
                    
                    MapIntSP::iterator it = productions1.find(index);
                    if (it == productions1.end()) {
                        productions1.insert(std::make_pair(index, set));
                    } else {
                        it->second = set;
                    }
                    modified = true;
                }
            } else {
                productions1.insert(std::make_pair(index, set));
                modified = true;
            }
        }
        
        if (modified) {
            return filterProductions(productions1, productions);
        } else {
            return productions0;
        }
    }
    
    bool Linearizer::filterRule(const MapIntSP& productions, gf::reader::Production* production) const {
        gf::reader::ApplProduction* appl;
        gf::reader::CoerceProduction* coerce;
        
        appl = dynamic_cast<gf::reader::ApplProduction*>(production);
        coerce = dynamic_cast<gf::reader::CoerceProduction*>(production);
        if (appl != NULL) {
            for (std::vector<uint32_t>::const_iterator it = appl->getArgs().begin(); it != appl->getArgs().end(); it++) {
                if (!conditionProd(*it, productions)) {
                    return false;
                }
            }
            
            return true;
        } else if (coerce != NULL) {
            return conditionProd(coerce->getInitId(), productions);
        } else {
            assert(0);
        }
    
    }
    
    bool Linearizer::isHoProduction(gf::reader::Production* production) const {
        gf::reader::ApplProduction* appl;
        
        appl = dynamic_cast<gf::reader::ApplProduction*>(production);
        if (appl == NULL) {
            return false;
        }
        
        // TODO: Strange constant in code.
        return appl->getArgs().size() == 1 && appl->getArgs().front() == -4;
    }
    
    std::set<uint32_t> Linearizer::getHoFIds() const {
        std::set<std::string> categories;
        std::set<uint32_t> ret;
        
        categories = getHoCategories();
        
        for (std::vector<gf::reader::CncCat*>::const_iterator cncCat = concrete->getCncCats().begin(); cncCat != concrete->getCncCats().end(); cncCat++) {
            if (categories.find((*cncCat)->getName()) == categories.end()) {
                continue;
            }
            
            for (uint32_t index = (*cncCat)->getFirstId(); index < (*cncCat)->getLastId(); index++) {
                ret.insert(index);
            }
        }
        
        
        return ret;
    }
    
    std::set<std::string> Linearizer::getHoCategories() const {
        std::set<std::string> ret;
        
        for (std::vector<gf::reader::AbsFun*>::const_iterator absFun = pgf->getAbstract()->getAbsFuns().begin(); absFun != pgf->getAbstract()->getAbsFuns().end(); absFun++) {
            for (std::vector<gf::reader::Hypo*>::const_iterator hypo = (*absFun)->getType()->getHypos().begin(); hypo != (*absFun)->getType()->getHypos().end(); hypo++) {
                ret.insert((*hypo)->getType()->getName());
            }
        }
        
        return ret;
    }
    
    std::vector<std::string> Linearizer::getHypoArgsOfType(gf::reader::Type* type) const {
        std::vector<std::string> ret;
        
        for (std::vector<gf::reader::Hypo*>::const_iterator hypo = type->getHypos().begin(); hypo != type->getHypos().end(); hypo++) {
            ret.push_back((*hypo)->getType()->getName());
        }
        
        return ret;
    }
    
    std::vector<std::string> Linearizer::untoken(gf::linearizer::BracketedToken* bt, const std::string& after) const {
        gf::linearizer::LeafKS* leafks;
        gf::linearizer::LeafKP* leafkp;
        gf::linearizer::Bracket* bracket;
        std::vector<std::string> ret;
        
        leafks = dynamic_cast<gf::linearizer::LeafKS*>(bt);
        leafkp = dynamic_cast<gf::linearizer::LeafKP*>(bt);
        bracket = dynamic_cast<gf::linearizer::Bracket*>(bt);
        if (leafks != NULL) {
            ret = leafks->getTokens();
            std::reverse(ret.begin(), ret.end());            
            return ret;
        } else if (leafkp != NULL) {
            for (std::vector<gf::reader::Alternative*>::const_iterator alt = leafkp->getAlternatives().begin(); alt != leafkp->getAlternatives().end(); alt++) {
                for (std::vector<std::string>::const_iterator it = (*alt)->getAlt2().begin(); it != (*alt)->getAlt2().end(); it++) {
                    if (after.substr(0, it->size()) != *it) {
                        continue;
                    }
                    
                    ret = (*alt)->getAlt1();
                    std::reverse(ret.begin(), ret.end());            
                    return ret;
                }
            }
            
            ret = leafks->getTokens();
            std::reverse(ret.begin(), ret.end());            
            return ret;
        } else if (bracket != NULL) {
            std::string last = after;
            
            for (std::vector<gf::linearizer::BracketedToken*>::const_reverse_iterator brk = bracket->getBracketedTokens().rbegin(); brk != bracket->getBracketedTokens().rend(); brk++) {
                std::vector<std::string> temp;
                
                temp = untoken(*brk, last);
                ret.insert(ret.end(), temp.begin(), temp.end());
            }
            
            return ret;
        } else {
            assert(0);
        }
    }
    
    std::vector<std::string> Linearizer::renderLin(gf::linearizer::LinTriple* triple) const {
        std::vector<std::string> ret;
        VBracketedToken front;
        std::string after;
        
        front = triple->getLinTable().front();
        for (VBracketedToken::const_reverse_iterator it = front.rbegin(); it != front.rend(); it++) {
            std::vector<std::string> temp;
            
            temp = untoken(*it, after);
            ret.insert(ret.end(), temp.begin(), temp.end());
            after = ret.back();
        }
        
        std::reverse(ret.begin(), ret.end());
        return ret;
    }
    
    std::vector<std::vector<std::string> > Linearizer::renderAllLins(const std::vector<gf::linearizer::LinTriple*>& triples) const {
        std::vector<std::vector<std::string> > ret;
        
        for (std::vector<gf::linearizer::LinTriple*>::const_iterator it = triples.begin(); it != triples.end(); it++) {
            ret.push_back(renderLin(*it));
        }
        
        return ret;
    }
    
    std::vector<gf::linearizer::LinTriple*> Linearizer::linearize(const Tree* tree) const throw (gf::LinearizerException) {
        std::vector<std::string> xs;
        
        return lin0(xs, std::vector<std::string>(), NULL, 0, tree);
    }
    
    std::vector<gf::linearizer::LinTriple*> Linearizer::lin0(std::vector<std::string>& xs, const std::vector<std::string>& ys, gf::linearizer::CncType* mb_cty, uint32_t mb_fid, const Tree* tree) const throw (gf::LinearizerException) {
        const Lambda* lambda;

#ifdef DEBUG
        fprintf(stderr, "lin0: %s\n", gf::PrintAbsyn().print(const_cast<Tree*>(tree)));
#endif
        
        lambda = dynamic_cast<const Lambda*>(tree);
        if (lambda != NULL) {
            xs.push_back(lambda->ident_);
            return lin0(xs, ys, mb_cty, mb_fid, lambda->tree_);
        } else if (xs.empty()) {
            const Application* appl;
            const Function* fun;
            std::vector<const Tree*> es;
            
            appl = dynamic_cast<const Application*>(tree);
            while (appl != NULL) {
                es.push_back(appl->tree_2);
                tree = appl->tree_1;
                appl = dynamic_cast<const Application*>(tree);                
            }
            
            fun = dynamic_cast<const Function*>(tree);
            if (fun != NULL) {
                return apply(xs, mb_cty, mb_fid, fun->ident_, es);
            } else {
                throw LinearizerException("Undefined construction for expressions.");
            }
        } else {
            std::vector<const Tree*> exprs;
            std::vector<gf::linearizer::LinTriple*> ret;
            
            xs.insert(xs.end(), ys.begin(), ys.end());
            exprs.push_back(tree);
            
            for (std::vector<std::string>::const_iterator it = xs.begin(); it != xs.end(); it++) {
                exprs.push_back(new Literal(new StringLiteral(*it)));
            }
            
            // TODO: Strange string constant.
            ret = apply(xs, mb_cty, mb_fid, "_B", exprs);
            
            for (std::vector<const Tree*>::iterator it = exprs.begin(); it != exprs.end(); it++) {
                delete *it;
            }
            
            return ret;
        }
    }
    
    std::vector<gf::linearizer::LinTriple*> Linearizer::apply(const std::vector<std::string>& xs, gf::linearizer::CncType* mb_cty, uint32_t n_fid, const std::string& function, const std::vector<const Tree*>& trees) const throw (gf::LinearizerException) {
        MapStrMapIntSP::const_iterator productions;
        
#ifdef DEBUG
        fprintf(stderr, "apply: %s\n", function.c_str());
#endif
        
        productions = lProductions.find(function);
        if (productions == lProductions.end()) {
            std::vector<const Tree*> exprs;
            std::vector<gf::linearizer::LinTriple*> ret;
            
            exprs.push_back(new Literal(new StringLiteral(function)));
            
            fprintf(stderr, "Function %s does not have a linearisation.", function.c_str());
            // TODO: Strange string constant.
            ret = apply(xs, mb_cty, n_fid, "_V", exprs);
            
            for (std::vector<const Tree*>::iterator it = exprs.begin(); it != exprs.end(); it++) {
                delete *it;
            }
            
            return ret;
        } else {
            std::vector<gf::linearizer::AppResult*> apps;
            std::vector<gf::linearizer::LinTriple*> ret;
            
            apps = getApps(productions->second, mb_cty, function);
            for (std::vector<gf::linearizer::AppResult*>::const_iterator itApp = apps.begin(); itApp != apps.end(); itApp++) {
                std::list<gf::linearizer::CncType*> cncTypes;
                std::vector<gf::reader::Sequence*> lins;
                std::string category;
                std::list<const Tree*> exprs;
                std::vector<gf::linearizer::RezDesc*> rezDesc;
                
                cncTypes.insert(cncTypes.end(), (*itApp)->getConcreteTypes().begin(), (*itApp)->getConcreteTypes().end());
                std::reverse(cncTypes.begin(), cncTypes.end());
                if (trees.size() != cncTypes.size()) {
                    std::string msg;
                    
                    msg = "Lengths of trees and concrete types does not match: [";
                    for (std::vector<const Tree*>::const_iterator it = trees.begin(); it != trees.end(); it++) {
                        if (it != trees.begin()) {
                            msg+= ", ";
                        }
                        msg+= gf::PrintAbsyn().print(const_cast<Tree*>(*it));
                    }
                    msg+= "] -- [";
                    for (std::list<gf::linearizer::CncType*>::const_iterator it = cncTypes.begin(); it != cncTypes.end(); it++) {
                        msg+= (it == cncTypes.begin() ? "" : ", ") + (*it)->toString();
                    }
                    msg+= "]";
                    
                    throw LinearizerException(msg);
                }
                
                lins = (*itApp)->getConcreteFunction()->getSequences();
                category = (*itApp)->getConcreteType()->getCId();
                exprs.insert(exprs.end(), trees.begin(), trees.end());
                
                rezDesc = descend(n_fid, cncTypes, exprs, xs);
                for (std::vector<gf::linearizer::RezDesc*>::const_iterator itRD = rezDesc.begin(); itRD != rezDesc.end(); itRD++) {
                    VVBracketedToken linTab;
                    
                    for (std::vector<gf::reader::Sequence*>::const_iterator itLin = lins.begin(); itLin != lins.end(); itLin++) {
                        linTab.push_back(computeSequence(*itLin, (*itRD)->getConcreteTypes(), (*itRD)->getBracketedTokens()));
                    }
                    
                    ret.push_back(new gf::linearizer::LinTriple(n_fid + 1, new gf::linearizer::CncType(category, n_fid), linTab));
                }
                
                for (std::vector<gf::linearizer::RezDesc*>::iterator itRD = rezDesc.begin(); itRD != rezDesc.end(); itRD++) {
                    gf::release(*itRD);
                }
            }
            
            for (std::vector<gf::linearizer::AppResult*>::iterator itApp = apps.begin(); itApp != apps.end(); itApp++) {
                gf::release(*itApp);
            }
            
#ifdef DEBUG
            fprintf(stderr, "apply -> [");
            for (std::vector<gf::linearizer::LinTriple*>::const_iterator it = ret.begin(); it != ret.end(); it++) {
                fprintf(stderr, "%s%s", it == ret.begin() ? "" : ", ", (*it)->toString().c_str());
            }
            fprintf(stderr, "]\n");
#endif
            
            return ret;
        }
    }
    
    std::vector<gf::linearizer::AppResult*> Linearizer::getApps(const MapIntSP& productions, gf::linearizer::CncType* mb_cty, const std::string& function) const throw (gf::LinearizerException) {
        std::vector<gf::linearizer::AppResult*> ret;
        
        if (mb_cty == NULL) {
            // TODO: Strange string constants.
            if (function == "_V" || function == "_B") {
                return ret;
            }
            
            for (MapIntSP::const_iterator it = productions.begin(); it != productions.end(); it++) {
                uint32_t fid = it->first;
                for (SetProd::const_iterator ip = it->second.begin(); ip != it->second.begin(); ip++) {
                    gf::linearizer::CncType* cty;
                    std::vector<gf::linearizer::AppResult*> temp;
                    /*
                    prod = *ip;
                    prod->addReference();
                    
                    for (MapIntSP::const_iterator itMap = productions.begin(); itMap != productions.end(); itMap++) {
                        for (SetProd::const_iterator itSet = itMap->second.begin(); itSet != itMap->second.end(); itSet++) {
                            (*itSet)->addReference();
                        }
                    }
                    */
                    
                    cty = new gf::linearizer::CncType("_", fid);
                    temp = toApp(cty, *ip, function, productions);
                    gf::release(cty);
                    
                    ret.insert(ret.end(), temp.begin(), temp.end());
                }

            }
            
            return ret;
        } else {
            MapIntSP::const_iterator it = productions.find(mb_cty->getFId());
            if (it == productions.end()) {
                return ret;
            }
            
            for (SetProd::const_iterator ip = it->second.begin(); ip != it->second.begin(); ip++) {
                std::vector<gf::linearizer::AppResult*> temp;
                
                temp = toApp(mb_cty, *ip, function, productions);
                
                ret.insert(ret.end(), temp.begin(), temp.end());
            }
            
            return ret;
        }
    }
    
    std::vector<gf::linearizer::AppResult*> Linearizer::toApp(gf::linearizer::CncType* cty, gf::reader::Production* production, const std::string& function, const MapIntSP& productions) const throw (gf::LinearizerException) {
        gf::reader::ApplProduction* appl;
        gf::reader::CoerceProduction* coerce;
        std::vector<gf::linearizer::AppResult*> ret;
        
        appl = dynamic_cast<gf::reader::ApplProduction*>(production);
        coerce = dynamic_cast<gf::reader::CoerceProduction*>(production);
        if (appl != NULL) {
            gf::reader::CncFun* cncFun;
            std::vector<gf::linearizer::CncType*> cncTypes;
            
            cncFun = appl->getFunction();
            
            // TODO: Shouldn't this be _V?
            if (function == "V") {
                for (std::vector<uint32_t>::const_iterator arg = appl->getArgs().begin(); arg != appl->getArgs().end(); arg++) {
                    cncTypes.push_back(new gf::linearizer::CncType("__gfVar", *arg));
                }
                
                cncFun->addReference();
                cty->addReference();
                ret.push_back(new gf::linearizer::AppResult(cncFun, cty, cncTypes));
                
                return ret;
            } else if (function == "_B") {
                assert(!appl->getArgs().empty());
                
                cncTypes.push_back(new gf::linearizer::CncType(cty->getCId(), appl->getArgs().front()));
                for (std::vector<uint32_t>::const_iterator arg = appl->getArgs().begin() + 1; arg != appl->getArgs().end(); arg++) {
                    cncTypes.push_back(new gf::linearizer::CncType("__gfVar", *arg));
                }
                
                cncFun->addReference();
                cty->addReference();
                ret.push_back(new gf::linearizer::AppResult(cncFun, cty, cncTypes));
                
                return ret;
            } else {
                gf::reader::Type* type = NULL;
                std::vector<std::string> catSkel;
                gf::linearizer::CncType* cncType;
                
                for (std::vector<gf::reader::AbsFun*>::const_iterator it = pgf->getAbstract()->getAbsFuns().begin(); it != pgf->getAbstract()->getAbsFuns().end(); it++) {
                    if ((*it)->getName() == function) {
                        type = (*it)->getType();
                    }
                }
                
                if (type == NULL) {
                    throw LinearizerException(function + " not found in the abstract syntax");
                }
                
                catSkel = catSkeleton(type);
                assert(catSkel.size() >= appl->getArgs().size() + 1);
                
                cncType = new gf::linearizer::CncType(catSkel.front(), cty->getFId());
                
                for (size_t i = 0; i < appl->getArgs().size(); i++) {
                    cncTypes.push_back(new gf::linearizer::CncType(catSkel.at(i + 1), appl->getArgs().at(i)));
                }
                
                cncFun->addReference();
                ret.push_back(new gf::linearizer::AppResult(cncFun, cncType, cncTypes));
                
                return ret;
            }
        } else if (coerce != NULL) {
            MapIntSP::const_iterator it = productions.find(coerce->getInitId());
            assert(it != productions.end());
            
            for (SetProd::const_iterator ip = it->second.begin(); ip != it->second.begin(); ip++) {
                std::vector<gf::linearizer::AppResult*> temp;
                
                temp = toApp(cty, *ip, function, productions);
                
                ret.insert(ret.end(), temp.begin(), temp.end());
            }
            
            return ret;
        } else {
            assert(0);
        }
    }
    
    std::vector<std::string> Linearizer::catSkeleton(gf::reader::Type* type) const {
        std::vector<std::string> ret;
        
        ret.push_back(type->getName());
        
        for (std::vector<gf::reader::Hypo*>::const_iterator hypo = type->getHypos().begin(); hypo != type->getHypos().end(); hypo++) {
            ret.push_back((*hypo)->getType()->getName());
        }
        
        return ret;
    }
    
    Linearizer::VVBracketedToken Linearizer::mkVVBracketedToken(const std::string& str) const {
        std::vector<std::string> tokens;
        VBracketedToken temp;
        VVBracketedToken ret;
        
        tokens.push_back(str);
        temp.push_back(new gf::linearizer::LeafKS(tokens));
        ret.push_back(temp);
        
        return ret;
    }
    
    Linearizer::VBracketedToken Linearizer::compute(gf::reader::Symbol* symbol, const std::vector<gf::linearizer::CncType*>& cncTypes, const VVVBracketedToken& linTables) const {
        gf::reader::AlternToksSymbol* altern;
        gf::reader::ArgConstSymbol* argconst;
        gf::reader::ToksSymbol* toks;
        
        altern = dynamic_cast<gf::reader::AlternToksSymbol*>(symbol);
        argconst = dynamic_cast<gf::reader::ArgConstSymbol*>(symbol);
        toks = dynamic_cast<gf::reader::ToksSymbol*>(symbol);
        if (argconst != NULL) {
            return getArg(argconst->getArg(), argconst->getCons(), cncTypes, linTables);
        } else if (altern != NULL) {
            std::vector<gf::reader::Alternative*> alts;
            Linearizer::VBracketedToken ret;
            
            alts = altern->getAlternatives();
            for (std::vector<gf::reader::Alternative*>::iterator it = alts.begin(); it != alts.end(); it++) {
                (*it)->addReference();
            }
            
            ret.push_back(new gf::linearizer::LeafKP(altern->getTokens(), alts));
            
            return ret;
        } else if (toks != NULL) {
            Linearizer::VBracketedToken ret;
            
            ret.push_back(new gf::linearizer::LeafKS(toks->getTokens()));
            
            return ret;
        } else {
            assert(0);
        }
    }
    
    Linearizer::VBracketedToken Linearizer::getArg(uint32_t d, uint32_t r, const std::vector<gf::linearizer::CncType*>& cncTypes, const VVVBracketedToken& linTables) const {
        VBracketedToken ret;
        gf::linearizer::CncType* cncType;
        VVBracketedToken lin;
        VBracketedToken argLin;
        
        if (cncTypes.size() <= d) {
            return ret;
        }
        
        cncType = cncTypes.at(d);
        lin = linTables.at(d);
        
        argLin = lin.at(r);
        if (argLin.empty()) {
            return ret;
        }
        
        for (VBracketedToken::iterator it = argLin.begin(); it != argLin.end(); it++) {
            (*it)->addReference();
        }
        
        ret.push_back(new gf::linearizer::Bracket(cncType->getCId(), cncType->getFId(), r, argLin));
        
        return ret;
    }
    
    Linearizer::VBracketedToken Linearizer::computeSequence(gf::reader::Sequence* sequence, const std::vector<gf::linearizer::CncType*>& cncTypes, const VVVBracketedToken& linTables) const {
        VBracketedToken ret;
        
        for (std::vector<gf::reader::Symbol*>::const_iterator sym = sequence->getSymbols().begin(); sym != sequence->getSymbols().end(); sym++) {
            VBracketedToken temp;
            
            temp = compute(*sym, cncTypes, linTables);
            ret.insert(ret.end(), temp.begin(), temp.end());
        }
        
        return ret;
    }
    
    std::vector<gf::linearizer::RezDesc*> Linearizer::descend(uint32_t n_fid, std::list<gf::linearizer::CncType*>& cncTypes, std::list<const Tree*>& trees, const std::vector<std::string>& xs) const throw (gf::LinearizerException) {
        std::vector<gf::linearizer::RezDesc*> ret;
        gf::linearizer::CncType* cncType;
        const Tree* exp;
        std::vector<std::string> empty;
        std::vector<gf::linearizer::LinTriple*> lins;
        std::vector<gf::linearizer::RezDesc*> rezDesc;
        
        if (trees.empty()) {
            ret.push_back(new gf::linearizer::RezDesc(n_fid, std::vector<gf::linearizer::CncType*>(), VVVBracketedToken()));
            return ret;
        }
        
        assert(!cncTypes.empty());
        
        cncType = cncTypes.front();
        cncTypes.pop_front();
        
        exp = trees.front();
        trees.pop_front();
        
        lins = lin0(empty, xs, cncType, n_fid, exp);
        
#ifdef DEBUG
        fprintf(stderr, "descend.lins: [");
        for (std::vector<gf::linearizer::LinTriple*>::const_iterator it = lins.begin(); it != lins.end(); it++) {
            fprintf(stderr, "%s%s", it == lins.begin() ? "" : ", ", (*it)->toString().c_str());
        }
        fprintf(stderr, "]\n");
#endif
      
        rezDesc = descend(n_fid, cncTypes, trees, xs);
        
        for (std::vector<gf::linearizer::LinTriple*>::const_iterator lin = lins.begin(); lin != lins.end(); lin++) {
            for (std::vector<gf::linearizer::RezDesc*>::const_iterator rd = rezDesc.begin(); rd != rezDesc.end(); rd++) {
                std::vector<gf::linearizer::CncType*> types;
                VVVBracketedToken tokens;
                
                types = (*rd)->getConcreteTypes();
                tokens = (*rd)->getBracketedTokens();
                
                types.push_back((*lin)->getConcreteType());
                tokens.push_back((*lin)->getLinTable());
                
                for (std::vector<gf::linearizer::CncType*>::iterator it = types.begin(); it != types.end(); it++) {
                    (*it)->addReference();
                }
                for (VVVBracketedToken::iterator it = tokens.begin(); it != tokens.end(); it++) {
                    for (VVBracketedToken::iterator it2 = it->begin(); it2 != it->end(); it2++) {
                        for (VBracketedToken::iterator it3 = it2->begin(); it3 != it2->end(); it3++) {
                            (*it3)->addReference();
                        }
                    }
                }
                
                ret.push_back(new gf::linearizer::RezDesc(n_fid, types, tokens));
            }
        }
        
        for (std::vector<gf::linearizer::LinTriple*>::iterator lin = lins.begin(); lin != lins.end(); lin++) {
            gf::release(*lin);
        }
        
        for (std::vector<gf::linearizer::RezDesc*>::iterator rd = rezDesc.begin(); rd != rezDesc.end(); rd++) {
            gf::release(*rd);
        }
        
        return ret;
    }
    
    bool Linearizer::isApplication(gf::reader::Production* production) const {
        return dynamic_cast<gf::reader::ApplProduction*>(production) != NULL;
    }
    
    bool Linearizer::isLiteralInt(int32_t i) const {
        // TODO: Strange integer constant.
        return i == -2;
    }
    
    bool Linearizer::isLiteralString(int32_t i) const {
        // TODO: Strange integer constant.
        return i == -1;
    }
    
    bool Linearizer::isLiteralFloat(int32_t i) const {
        // TODO: Strange integer constant.
        return i == -3;
    }
    
    bool Linearizer::isLiteralVar(int32_t i) const {
        // TODO: Strange integer constant.
        return i == -4;
    }
    
    bool Linearizer::isLiteral(int32_t i) const {
        return isLiteralInt(i) || isLiteralString(i) || isLiteralFloat(i) || isLiteralVar(i);
    }
    
}
