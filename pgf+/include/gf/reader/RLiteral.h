//
//  RLiteral.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__RLiteral_h
#define pgf__RLiteral_h

#include <string>

namespace gf {
    namespace reader {
        
        class RLiteral {
        private:
            
        public:
            RLiteral();
            virtual ~RLiteral();
            
            virtual std::string toString() const = 0;
        };
        
    }
}

#endif
