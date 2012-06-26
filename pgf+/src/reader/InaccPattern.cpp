//
//  InaccPattern.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/InaccPattern.h>

namespace gf {
    namespace reader {
        
        InaccPattern::InaccPattern(Expr* expr)
            : expr(expr) {
        }
        
        InaccPattern::~InaccPattern() {
            gf::release(expr);
        }
        
        Expr* InaccPattern::getExpr() const {
            return expr;
        }
        
        std::string InaccPattern::toString() const {
            return "Inaccessible pattern: " + expr->toString();
        }
        
    }
}