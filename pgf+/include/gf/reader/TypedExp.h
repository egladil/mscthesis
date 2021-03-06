//
//  TypedExp.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__TypedExp_h
#define pgf__TypedExp_h

#include <gf/reader/Expr.h>
#include <gf/reader/Type.h>

namespace gf {
    namespace reader {
        
        class TypedExp : public Expr {
        private:
            Expr* expression;
            Type* type;
            
        public:
            /**
             * Create a TypedExp object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference.
             */
            TypedExp(Expr* expression, Type* type);
            virtual ~TypedExp();
            
            virtual Expr* getExpression();
            virtual Type* getType();
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
