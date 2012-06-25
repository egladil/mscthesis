//
//  AbsNameExp.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__AbsNameExp_h
#define pgf__AbsNameExp_h

#include <string>
#include <gf/reader/Expr.h>

namespace gf {
    namespace reader {
        
        class AbsNameExp : public Expr {
        private:
            std::string name;
            
        public:
            AbsNameExp(const std::string& name);
            virtual ~AbsNameExp();
            
            virtual const std::string& getName() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
