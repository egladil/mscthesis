//
//  ImplExp.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/ImplExp.h>

namespace gf {
    namespace reader {
        
        ImplExp::ImplExp(Expr* expr) 
            : expr(expr) {
        }
        
        ImplExp::~ImplExp() {
            gf::release(expr);
        }
        
        Expr* ImplExp::getExp() const {
            return expr;
        }
        
        std::string ImplExp::toString() const {
            return "Implicit argument expression: [" + expr->toString() + "]";
        }
        
    }
}