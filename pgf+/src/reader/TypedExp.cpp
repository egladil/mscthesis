//
//  TypedExp.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/TypedExp.h>

namespace gf {
    namespace reader {
        
        TypedExp::TypedExp(Expr* expression, Type* type)
            : expression(expression), type(type) {
        }
        
        TypedExp::~TypedExp() {
            gf::release(expression);
            gf::release(type);
        }
        
        Expr* TypedExp::getExpression() {
            return expression;
        }
        
        Type* TypedExp::getType() {
            return type;
        }
        
        std::string TypedExp::toString() const {
            std::string ret;
            
            ret = "Typed expression: [expr: ";
            ret+= expression->toString();
            ret+= ", type: ";
            ret+= type->toString();
            ret+= "]";
            
            return ret;
        }
        
    }
}