//
//  Eq.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__Eq_h
#define pgf__Eq_h

#include <vector>

#include <gf/RefBase.h>
#include <gf/reader/Expr.h>
#include <gf/reader/Pattern.h>

namespace gf {
    namespace reader {
        
        class Eq : public gf::RefBase {
        private:
            std::vector<Pattern*> patts;
            Expr* expr;
            
        public:
            /**
             * Create an Eq object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            Eq(const std::vector<Pattern*>& patterns, Expr* expression);
            virtual ~Eq();
            
            virtual const std::vector<Pattern>& patterns() const;
            virtual Expr* expression() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
