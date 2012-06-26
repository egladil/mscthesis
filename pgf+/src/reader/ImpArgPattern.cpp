//
//  ImpArgPattern.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/ImpArgPattern.h>

namespace gf {
    namespace reader {
        
        ImpArgPattern::ImpArgPattern(Pattern* name)
            : name(name) {
        }
        
        ImpArgPattern::~ImpArgPattern() {
            gf::release(name);
        }
        
        Pattern* ImpArgPattern::getName() const {
            return name;
        }
        
        std::string ImpArgPattern::toString() const {
            return "Implicit argument pattern: " + name->toString();
        }
        
    }
}