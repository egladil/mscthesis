//
//  ProductionSet.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/reader/ProductionSet.h>

namespace gf {
    namespace reader {
        
        ProductionSet::ProductionSet(uint32_t id, const std::vector<Production*>& productions)
        : id(id), productions(productions) {
        }
        
        ProductionSet::~ProductionSet() {
            for (std::vector<Production*>::iterator it = productions.begin(); it != productions.end(); it++) {
                gf::release(*it);
            }
        }
        
        size_t ProductionSet::length() const {
            return productions.size();
        }
        const std::vector<Production*>& ProductionSet::getProductions() const {
            return productions;
        }
        
        std::string ProductionSet::toString() const {
            std::string ret;
            
            ret = "Id: ";
            ret+= gf::toString(id);
            ret+= ", productions: [";
            for (std::vector<Production*>::const_iterator it = productions.begin(); it != productions.end(); it++) {
                ret+= (it == productions.begin() ? "" : " ") + (*it)->toString();
            }
            ret+= "]";
            
            return ret;
        }
        
        uint32_t ProductionSet::getId() const {
            return id;
        }
        
        // TODO: Cache set?
        ProductionPointerSet ProductionSet::getSetOfProductions() const {
            ProductionPointerSet ret;
            
            for (std::vector<Production*>::const_iterator it = productions.begin(); it != productions.end(); it++) {
                ret.insert(*it);
            }
            
            return ret;
        }
        
    }
}