//
//  Expr.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef pgf__Expr_h
#define pgf__Expr_h

#include <string>

namespace gf {
    namespace reader {
        
        class Expr {
        private:
            
        public:
            Expr();
            virtual ~Expr();
            
            virtual std::string toString() const = 0;
        };
        
    }
}

#endif
