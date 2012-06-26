//
//  IntLit.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/reader/IntLit.h>

namespace gf {
    namespace reader {
        
        IntLit::IntLit(int32_t value) 
            : value(value) {
        }
        
        IntLit::~IntLit() {
        }
        
        std::string IntLit::toString() const {
            return "Integer literal: " + gf::toString(value);
        }
        
        int32_t IntLit::getValue() const {
            return value;
        }
        
    }
}