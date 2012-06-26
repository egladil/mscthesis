//
//  ArgConstSymbol.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/reader/ArgConstSymbol.h>

namespace gf {
    namespace reader {
        
        ArgConstSymbol::ArgConstSymbol(int32_t arg, int32_t cons)
            : arg(arg), cons(cons) {
        }
        
        ArgConstSymbol::~ArgConstSymbol() {
        }
        
        int32_t ArgConstSymbol::getArg() const {
            return arg;
        }
        
        int32_t ArgConstSymbol::getCons() const {
            return cons;
        }
        
        std::string ArgConstSymbol::toString() const {
            std::string ret;
            
            ret = "Argument: ";
            ret+= gf::toString(arg);
            ret+= ", constituent: ";
            ret+= gf::toString(cons);
            
            return ret;
        }
        
    }
}