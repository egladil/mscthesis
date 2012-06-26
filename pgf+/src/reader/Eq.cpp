//
//  Eq.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/Eq.h>

namespace gf {
    namespace reader {
        
        Eq::Eq(const std::vector<Pattern*>& patterns, Expr* expression)
            : patterns(patterns), expr(expression) {
        }
        
        Eq::~Eq() {
            for (std::vector<Pattern*>::iterator it = patterns.begin(); it != patterns.end(); it++) {
                gf::release(*it);
            }
            
            gf::release(expr);
        }
        
        const std::vector<Pattern*>& Eq::getPatterns() const {
            return patterns;
        }
        
        Expr* Eq::getExpression() const {
            return expr;
        }
        
        std::string Eq::toString() const {
            std::string ret;
            
            ret = "Patterns: (";
            for (std::vector<Pattern*>::const_iterator it = patterns.begin(); it != patterns.end(); it++) {
                ret+= (it == patterns.begin() ? "" : " ") + (*it)->toString();
            }
            ret+= "), expression: ";
            ret+= expr->toString();
            
            return ret;
        }
        
    }
}