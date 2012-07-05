//
//  Chart.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-05.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <assert.h>
#include <gf/stringutil.h>
#include <gf/parser/Chart.h>
#include <gf/reader/CoerceProduction.h>

namespace gf {
    namespace parser {
        
        Chart::Chart(uint32_t nextCategory)
            : nextCategory(nextCategory) {
        }
        
        Chart::~Chart() {
            for (std::map<uint32_t, std::set<gf::reader::Production*> >::iterator it = productionSets.begin(); it != productionSets.end(); it++) {
                for (std::set<gf::reader::Production*>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                    (*it2)->release();
                }
                it->second.clear();
            }
            
        }
        
        bool Chart::addProduction(gf::reader::Production* production) {
            std::map<uint32_t, std::set<gf::reader::Production*> >::iterator set;
            std::set<gf::reader::Production*>::const_iterator it;
            
            set = productionSets.find(production->getCategory());
            if (set == productionSets.end()) {
                set = productionSets.insert(std::make_pair(production->getCategory(), std::set<gf::reader::Production*>())).first;
            } else {
                it = set->second.find(production);
                if (it != set->second.end()) {
                    return false;
                }
            }
            
            set->second.insert(production);
            nextCategory = std::max(nextCategory, production->getCategory() + 1);
            
            return true;
        }
        
        bool Chart::addProduction(uint32_t category, gf::reader::CncFun* function, const std::vector<uint32_t>& domain) {
            return addProduction(new gf::reader::ApplProduction(category, function, domain));
        }
        
        std::vector<gf::reader::ApplProduction*> Chart::getProductions(uint32_t resultCategory) const {
            std::map<uint32_t, std::set<gf::reader::Production*> >::const_iterator set;
            std::vector<gf::reader::ApplProduction*> ret;
            
            set = productionSets.find(resultCategory);
            if (set == productionSets.end()) {
                return ret;
            }
            
            for (std::set<gf::reader::Production*>::const_iterator it = set->second.begin(); it != set->second.end(); it++) {
                std::vector<gf::reader::ApplProduction*> tmp;
                
                tmp = uncoerce(*it);
                ret.insert(ret.end(), tmp.begin(), tmp.end());
            }
            
            return ret;
        }
        
        std::vector<gf::reader::ApplProduction*> Chart::uncoerce(gf::reader::Production* production) const {
            gf::reader::ApplProduction* appl;
            gf::reader::CoerceProduction* coerce;
            std::vector<gf::reader::ApplProduction*> ret;
            
            appl = dynamic_cast<gf::reader::ApplProduction*>(production);
            coerce = dynamic_cast<gf::reader::CoerceProduction*>(production);
            if (appl != NULL) {
                appl->addReference();
                ret.push_back(appl);
                return ret;
            } else if (coerce != NULL) {
                std::vector<gf::reader::ApplProduction*> tmp;
                
                tmp = getProductions(coerce->getInitId());
                for (std::vector<gf::reader::ApplProduction*>::const_iterator it = tmp.begin(); it != tmp.end(); it++) {
                    std::vector<gf::reader::ApplProduction*> tmp2;
                    
                    // TODO: Is this needed?
                    // TODO: Might cause memory leaks.
                    tmp2 = uncoerce(*it);
                    ret.insert(ret.end(), tmp2.begin(), tmp2.end());
                }
            } else {
                assert(0);
            }
        }
        
        std::vector<uint32_t> Chart::mkCategoryBookKey(uint32_t oldCat, uint32_t cons, uint32_t begin, uint32_t end) const {
            std::vector<uint32_t> ret;
            
            ret.push_back(oldCat);
            ret.push_back(cons);
            ret.push_back(begin);
            ret.push_back(end);
            
            return ret;
        }
        
        
        uint32_t Chart::getFreshCategory(uint32_t oldCat, uint32_t cons, uint32_t begin, uint32_t end) {
            std::map<std::vector<uint32_t>, uint32_t>::const_iterator it;
            
            it = categoryBookKeeper.find(mkCategoryBookKey(oldCat, cons, begin, end));
            if (it == categoryBookKeeper.end()) {
                return generateFreshCategory(oldCat, cons, begin, end);
            }

            return it->second;
        }
        
        bool Chart::hasCategory(uint32_t oldCat, uint32_t cons, uint32_t begin, uint32_t end) const {
            std::map<std::vector<uint32_t>, uint32_t>::const_iterator it;
            
            it = categoryBookKeeper.find(mkCategoryBookKey(oldCat, cons, begin, end));
            return it != categoryBookKeeper.end();
        }
        
        uint32_t Chart::getCategory(uint32_t oldCat, uint32_t cons, uint32_t begin, uint32_t end) const throw (gf::ParseException) {
            std::map<std::vector<uint32_t>, uint32_t>::const_iterator it;
            
            it = categoryBookKeeper.find(mkCategoryBookKey(oldCat, cons, begin, end));
            if (it == categoryBookKeeper.end()) {
                throw gf::ParseException("getCategory() on unknown category");
            }
            
            return it->second;
        }
        
        uint32_t Chart::generateFreshCategory(uint32_t oldCat, uint32_t cons, uint32_t begin, uint32_t end) {
            uint32_t cat;
            
            cat = nextCategory;
            nextCategory++;
            
            categoryBookKeeper.insert(std::make_pair(mkCategoryBookKey(oldCat, cons, begin, end), cat));
            
            return cat;
        }
        
        std::string Chart::toString() const {
            std::string ret;
            
            ret = "=== Productions: ===\n";
            for (std::map<uint32_t, std::set<gf::reader::Production*> >::const_iterator it = productionSets.begin(); it != productionSets.end(); it++) {
                ret+= "[";
                for (std::set<gf::reader::Production*>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                    ret+= (it2 == it->second.begin() ? "" : ", ") + (*it2)->toString();
                }
                ret+= "]\n";
            }
            ret+= "=== passive items: ===\n";
            for (std::map<std::vector<uint32_t>, uint32_t>::const_iterator it = categoryBookKeeper.begin(); it != categoryBookKeeper.end(); it++) {
                ret+= "(";
                for (std::vector<uint32_t>::const_iterator it2 = it->first.begin(); it2 != it->first.end(); it2++) {
                    ret+= (it2 == it->first.begin() ? "" : ", ") + gf::toString(*it2);
                }
                ret+= ") -> " + gf::toString(it->second) + "\n";
            }
            
            return ret;
        }
        
    }
}

