//
//  StringLit.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/StringLit.h>

namespace gf {
    namespace reader {
        
        StringLit::StringLit(const std::string& value)
            : value(value) {
        }
        
        StringLit::~StringLit() {
        }
        
        std::string StringLit::toString() const {
            return "String literal: " + value;
        }
        
        const std::string& StringLit::getValue() const {
            return value;
        }
        
    }
}