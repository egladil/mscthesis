//
//  VarPattern.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/VarPattern.h>

namespace gf {
    namespace reader {
        
        VarPattern::VarPattern(const std::string& name)
            : name(name) {
        }
        
        VarPattern::~VarPattern() {
        }
        
        const std::string& VarPattern::getName() const {
            return name;
        }
        
        std::string VarPattern::toString() const {
            return "Variable pattern: " + name;
        }
        
    }
}