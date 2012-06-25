//
//  InaccPattern.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__InaccPattern_h
#define pgf__InaccPattern_h

#include <gf/reader/Expr.h>
#include <gf/reader/Pattern.h>

namespace gf {
    namespace reader {
        
        class InaccPattern : public Pattern {
        private:
            Expr* expr;
            
        public:
            /**
             * Create an InaccPattern object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            InaccPattern(Expr* expr);
            virtual ~InaccPattern();
            
            virtual Expr* getExpr() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
