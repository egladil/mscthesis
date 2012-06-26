//
//  Concrete.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/UnknownCategoryException.h>
#include <gf/reader/Concrete.h>

namespace gf {
    namespace reader {
        
        Concrete::Concrete(const std::string& name, const std::map<std::string, RLiteral*>& flags, const std::vector<Sequence*>& sequences, const std::vector<CncFun*>& cncFuns, const std::vector<ProductionSet*>& productions, const std::map<std::string, CncCat*>& cncCats, int32_t fId, const std::string& startCat)
        : name(name), flags(flags), sequences(sequences), cncFuns(cncFuns), cncCats(cncCats), fId(fId), startCat(startCat) {   
        }
        
        Concrete::~Concrete() {
        }
        
        const std::string& Concrete::getName() const {
            return name;
        }
        
        /**
         * returns the concretes categories (forest indices) corresponding to the
         * given abstract category.
         * @param absCat the name of the abstract category
         * @return the CncCat object
         * @throws gf::UnknownCategoryException if the category is unknown
         **/
        CncCat* Concrete::concreteCat(const std::string& absCat) const {
            std::map<std::string, CncCat*>::const_iterator it = cncCats.find(absCat);
            if (it == cncCats.end()) {
                throw UnknownCategoryException(absCat);
            }
            
            return it->second;
        }
        
        const std::vector<Sequence*>& Concrete::getSequences() const {
            return sequences;
        }
        
        const std::vector<CncFun*>& Concrete::getCncFuns() const {
            return cncFuns;
        }
        
        const std::vector<ProductionSet*>& Concrete::getProductionSets() const {
            return productions;
        }
        
        // TODO: Cache vector?
        std::vector<CncCat*> Concrete::getCncCats() const {
            std::vector<CncCat*> ret;
            
            for (std::map<std::string, CncCat*>::const_iterator it = cncCats.begin(); it != cncCats.end(); it++) {
                ret.push_back(it->second);
            }
            
            return ret;
        }
        
        int32_t Concrete::getFId() const {
            return fId;
        }
        
        const CncCat* Concrete::getStartCat() const {
            std::map<std::string, CncCat*>::const_iterator it = cncCats.find(startCat);
            if (it != cncCats.end()) {
                return it->second;
            }
            
            return new CncCat(startCat, 0, 0, std::vector<std::string>());
        }
        
        // TODO: Cache vector?
        std::vector<Production*> Concrete::getProductions() const {
            std::vector<Production*> ret;
            
            for (std::vector<ProductionSet*>::const_iterator it = productions.begin(); it != productions.end(); it++) {
                ProductionSet* ps = *it;
                
                for (std::vector<Production*>::const_iterator it2 = ps->getProductions().begin(); it2 != ps->getProductions().end(); it2++) {
                    ret.push_back(*it2);
                }
            }
            
            return ret;
        }
        
        std::string Concrete::toString() const {
            return "concrete " + name;
        }
        
        // TODO: Cache map?
        std::map<uint32_t, std::set<Production*> > Concrete::getSetOfProductions() const {
            std::map<uint32_t, std::set<Production*> > ret;
            
            for (std::vector<ProductionSet*>::const_iterator it = productions.begin(); it != productions.end(); it++) {
                ProductionSet* ps = *it;
                
                ret.insert(std::make_pair(ps->getId(), ps->getSetOfProductions()));
            }
            
            
            return ret;
        }
        
    }
}