//
//  Pattern.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__Pattern_h
#define pgf__Pattern_h

#include <string>

namespace gf {
    namespace reader {
        
        class Pattern {
        private:
            
        public:
            Pattern();
            virtual ~Pattern();
            
            virtual std::string toString() const = 0;
        };
        
    }
}

#endif
