//
//  AppExp.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__AppExp_h
#define pgf__AppExp_h

#include <gf/reader/Expr.h>

namespace gf {
    namespace reader {
        
        class AppExp : public Expr {
        private:
            Expr* lExp;
            Expr* rExp;
            
        public:
            /**
             * Create an AppExp object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            AppExp(Expr* lExp, Expr* rExp);
            virtual ~AppExp();
            
            virtual Expr* getLeftExpr() const;
            virtual Expr* getRightExpr() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
