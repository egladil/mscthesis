//
//  StringLit.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__StringLit_h
#define pgf__StringLit_h

#include <string>
#include <gf/reader/RLiteral.h>

namespace gf {
    namespace reader {
        
        class StringLit : public RLiteral {
        private:
            std::string value;
            
        public:
            StringLit(const std::string& value);
            
            virtual std::string toString() const;
            
            virtual const std::string& getValue() const;
            
        };
        
    }
}


#endif
