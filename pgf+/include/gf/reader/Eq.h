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

#include <gf/reader/Expr.h>
#include <gf/reader/Pattern.h>

namespace gf {
    namespace reader {
        
        class Eq {
        private:
            std::vector<Pattern> patts;
            Expr expr;
            
        public:
            Eq(const std::vector<Pattern>& patterns, Expr expression);
            virtual ~Eq();
            
            virtual const std::vector<Pattern>& patterns() const;
            virtual const Expr& expression() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
