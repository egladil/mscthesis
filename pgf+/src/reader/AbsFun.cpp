//
//  AbsFun.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/AbsFun.h>

namespace gf {
    namespace reader {
        
        AbsFun::AbsFun(const std::string& name, Type* type, int32_t arity, const std::vector<Eq*>& eqs, double weight)
            : name(name), type(type), arity(arity), eqs(eqs), weight(weight) {
        }
        
        AbsFun::~AbsFun() {
            gf::release(type);
            
            for (std::vector<Eq*>::iterator it = eqs.begin(); it != eqs.end(); it++) {
                gf::release(*it);
            }
        }
        
        const std::string& AbsFun::getName() const {
            return name;
        }
        
        const Type* AbsFun::getType() const {
            return type;
        }
        
        int32_t AbsFun::getArity() const {
            return arity;
        }
        
        const std::vector<Eq*>& AbsFun::getEqs() const {
            return eqs;
        }
        
        double AbsFun::getWeight() const {
            return weight;
        }
        
        std::string AbsFun::toString() const {
            return name + ": " + type->toString();
        }
    }
}