//
//  CncCat.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/reader/CncCat.h>

namespace gf {
    namespace reader {
        
        CncCat::CncCat(const std::string& name, uint32_t firstFId, uint32_t lastFId, const std::vector<std::string>& labels)
            : name(name), firstFId(firstFId), lastFId(lastFId) {
        }
        
        CncCat::~CncCat() {
        }
        
        std::string CncCat::toString() const {
            std::string ret;
            
            ret = name;
            ret+= " [";
            ret+= name;
            ret+= "::C";
            ret+= gf::toString(firstFId);
            ret+=  " ... C";
            ret+= gf::toString(lastFId);
            ret+= "]";
            
            return ret;
        }
        
        const std::string& CncCat::getName() const {
            return name;
        }
        
        uint32_t CncCat::getFirstId() const {
            return firstFId;
        }
        
        uint32_t CncCat::getLastId() const {
            return lastFId;
        }
        
    }
}