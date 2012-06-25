//
//  LiteralExp.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__LiteralExp_h
#define pgf__LiteralExp_h

#include <gf/reader/Expr.h>
#include <gf/reader/RLiteral.h>

namespace gf {
    namespace reader {
        
        class LiteralExp : public Expr {
        private:
            RLiteral* value;
            
        public:
            /**
             * Create a LiteralExp object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            LiteralExp(RLiteral* value);
            virtual ~LiteralExp();
            
            virtual RLiteral* getValue() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
