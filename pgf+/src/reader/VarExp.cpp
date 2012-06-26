//
//  VarExp.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/reader/VarExp.h>

namespace gf {
    namespace reader {
        
        VarExp::VarExp(uint32_t index)
            : index(index) {
        }
        
        VarExp::~VarExp() {
        }
        
        uint32_t VarExp::getVarIndex() const {
            return index;
        }
        
        std::string VarExp::toString() const {
            return "Variable expression: [index: " + gf::toString(index) + "]";
        }
        
    }
}
