//
//  LambdaExp.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/LambdaExp.h>

namespace gf {
    namespace reader {
        
        LambdaExp::LambdaExp(bool boundType, const std::string& variableName, Expr* body)
            : boundType(boundType), variableName(variableName), body(body) {
        }
        
        LambdaExp::~LambdaExp() {
            gf::release(body);
        }
        
        bool LambdaExp::getType() const {
            return boundType;
        }
        
        const std::string& LambdaExp::getVarName() const {
            return variableName;
        }
        
        Expr* LambdaExp::getBody() const {
            return body;
        }
        
        std::string LambdaExp::toString() const {
            std::string ret;
            
            ret = "Lambda expression: [Bound type: ";
            ret+= boundType ? "true" : "false";
            ret+= ", name: ";
            ret+= variableName;
            ret+= ", body: ";
            ret+= body->toString();
            ret+= "]";
            
            return ret; 
        }
        
    }
}