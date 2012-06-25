//
//  VarExp.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__VarExp_h
#define pgf__VarExp_h

#include <gf/reader/Expr.h>

namespace gf {
    namespace reader {
        
        class VarExp : public Expr {
        private:
            uint32_t index;
            
        public:
            VarExp(uint32_t index);
            virtual ~VarExp();
            
            virtual uint32_t getVarInd() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
