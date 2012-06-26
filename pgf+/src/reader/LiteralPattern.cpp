//
//  LiteralPattern.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/LiteralPattern.h>

namespace gf {
    namespace reader {
        
        LiteralPattern::LiteralPattern(RLiteral* literal)
            : literal(literal) {
        }
        
        LiteralPattern::~LiteralPattern() {
            gf::release(literal);
        }
        
        RLiteral* LiteralPattern::getLit() const {
            return literal;
        }
        
        std::string LiteralPattern::toString() const {
            return "Literal pattern: " + literal->toString();
        }
        
    }
}
