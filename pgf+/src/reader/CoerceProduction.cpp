//
//  CoerceProduction.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/reader/CoerceProduction.h>

namespace gf {
    namespace reader {
        
        CoerceProduction::CoerceProduction(uint32_t fId, uint32_t initId)
            : Production(1, fId), initId(initId) {
            domain.push_back(initId);
        }
        
        CoerceProduction::~CoerceProduction() {
        }
        
        std::string CoerceProduction::toString() const {
            std::string ret;
            
            ret = "Coercion(";
            ret+= gf::toString(fId);
            ret+= " -> ";
            ret+= gf::toString(initId);
            ret+= ")";
            
            return ret;
        }
        
        bool CoerceProduction::operator<(const Production* other) const {
            const CoerceProduction* coerce = dynamic_cast<const CoerceProduction*>(other);
            
            if (coerce == NULL) {
                return this < other;
            }
            
            return initId < coerce->initId;
        }
        
        const std::vector<uint32_t>& CoerceProduction::getDomain() const {
            return domain;
        }
        
        uint32_t CoerceProduction::getInitId() const {
            return initId;
        }
        
    }
}