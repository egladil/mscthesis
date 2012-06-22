//
//  Symbol.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef pgf__Symbol_h
#define pgf__Symbol_h

#include <string>

namespace gf {
    namespace reader {
        
        class Symbol {
        private:
            
        public:
            Symbol();
            virtual ~Symbol();
            
            virtual std::string toString() const = 0;
        };
        
    }
}

#endif
