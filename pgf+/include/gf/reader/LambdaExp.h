//
//  LambdaExp.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__LambdaExp_h
#define pgf__LambdaExp_h

#include <string>
#include <gf/reader/Expr.h>

namespace gf {
    namespace reader {
        
        class LambdaExp : public Expr {
        private:
            bool boundType;
            std::string variableName;
            Expr* body;
            
        public:
            LambdaExp(bool boundType, const std::string& variableName, Expr* body);
            virtual ~LambdaExp();
            
            virtual bool getType() const;
            virtual const std::string& getVarName() const;
            virtual Expr* getBody() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
