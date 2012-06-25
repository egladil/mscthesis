//
//  Expr.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__Expr_h
#define pgf__Expr_h

#include <string>

#include <gf/RefBase.h>

namespace gf {
    namespace reader {
        
        class Expr : public gf::RefBase {
        private:
            
        public:
            Expr();
            virtual ~Expr();
            
            virtual std::string toString() const = 0;
        };
        
    }
}

#endif
