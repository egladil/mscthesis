//
//  VarAsPattern.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/VarAsPattern.h>

namespace gf {
    namespace reader {
        
        VarAsPattern::VarAsPattern(const std::string& name, Pattern* pattern)
            : name(name), pattern(pattern) {
        }
        
        VarAsPattern::~VarAsPattern() {
            gf::release(pattern);
        }
        
        const std::string& VarAsPattern::getName() const {
            return name;
        }
        
        Pattern* VarAsPattern::getPattern() const {
            return pattern;
        }
        
        std::string VarAsPattern::toString() const {
            std::string ret;
            
            ret = "Variable as pattern: [name: ";
            ret+= name;
            ret+= ", pattern: ";
            ret+= pattern->toString();
            ret+= "]";
            
            return ret;
        }
        
    }
}