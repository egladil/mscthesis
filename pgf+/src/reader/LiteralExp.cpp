//
//  LiteralExp.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/LiteralExp.h>

namespace gf {
    namespace reader {
        
        LiteralExp::LiteralExp(RLiteral* value)
            : value(value) {
        }
        
        LiteralExp::~LiteralExp() {
            gf::release(value);
        }
        
        RLiteral* LiteralExp::getValue() const {
            return value;
        }
        
        std::string LiteralExp::toString() const {
            return "Literal expression: " + value->toString();
        }
        
    }
}
