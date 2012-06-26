//
//  AppExp.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/AppExp.h>

namespace gf {
    namespace reader {
        
        AppExp::AppExp(Expr* lExp, Expr* rExp)
            : lExp(lExp), rExp(rExp) {
        }
        
        AppExp::~AppExp() {
            gf::release(lExp);
            gf::release(rExp);
        }
        
        Expr* AppExp::getLeftExpr() const {
            return lExp;
        }
        
        Expr* AppExp::getRightExpr() const {
            return rExp;
        }
        
        std::string AppExp::toString() const {
            std::string ret;
            
            ret = "Expression application [left hand side: (";
            ret+= lExp->toString();
            ret+= "), right hand side (";
            ret+= rExp->toString();
            ret+= ")]";
            
            return ret;
        }
        
    }
}