//
//  ApplProduction.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/reader/ApplProduction.h>

namespace gf {
    namespace reader {
        
        ApplProduction::ApplProduction(uint32_t fId, CncFun* function, const std::vector<uint32_t>& domain)
            : Production(0, fId), function(function), domain(domain) {
        }
        
        ApplProduction::~ApplProduction() {
            gf::release(function);
        }
        
        std::string ApplProduction::toString() const {
            std::string ret;
            
            ret = gf::toString(fId);
            ret+= " -> ";
            ret+= function->getName();
            ret+= "[";
            for (std::vector<uint32_t>::const_iterator it = domain.begin(); it != domain.end(); it++) {
                ret+= (it == domain.begin() ? "" : " ") + gf::toString(*it);
            }
            ret+= "]";
            
            return ret;
        }
        
        bool ApplProduction::operator<(const Production* other) const {
            const ApplProduction* appl;
            
            appl = dynamic_cast<const ApplProduction*>(other);
            if (appl == NULL) {
                return this < other;
            }
            
            if (function < appl->function) {
                return true;
            } else if (function > appl->function) {
                return false;
            }
            
            return domain < appl->domain;
        }
        
        const std::vector<uint32_t>& ApplProduction::getDomain() const {
            return domain;
        }
        
        CncFun* ApplProduction::getFunction() const {
            return function;
        }
        
        const std::vector<uint32_t>& ApplProduction::getArgs() const {
            return domain;
        }
        
    }
}