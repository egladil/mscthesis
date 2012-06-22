//
//  Type.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef pgf__Type_h
#define pgf__Type_h

#include <string>
#include <vector>

#include <gf/reader/Expr.h>
#include <gf/reader/Hypo.h>

namespace gf {
    namespace reader {
        
        class Type {
        private:
            std::vector<Hypo> hypos;
            std::string str;
            std::vector<Expr> exprs;
            
        public:
            Type(const std::vector<Hypo>& hypos, const std::string str, const std::vector<Expr>& exprs);
            virtual ~Type();
            
            virtual std::string toString() const;
            
            virtual const std::vector<Hypo>& getHypos() const;
            virtual const std::string& getName() const;
            virtual const std::vector<Expr>& getExprs() const;
            
            virtual bool isFunctionType() const;
            virtual bool isFunctorType() const;
        };
        
    }
}

#endif
