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
            Expr* expr;
            Type* type;
            
        public:
            TypedExp(Expr* expr, Type* type);
            virtual ~TypedExp();
            
            virtual Expr* getExp();
            virtual Type* getType();
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
