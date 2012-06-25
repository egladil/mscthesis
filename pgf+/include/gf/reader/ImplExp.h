//
//  ImplExp.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__ImplExp_h
#define pgf__ImplExp_h

#include <gf/reader/Expr.h>

namespace gf {
    namespace reader {
        
        class ImplExp : public Expr {
        private:
            Expr* expr;
            
        public:
            /**
             * Create an ImplExp object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            ImplExp(Expr* expr);
            virtual ~ImplExp();
            
            virtual Expr* getExp() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
