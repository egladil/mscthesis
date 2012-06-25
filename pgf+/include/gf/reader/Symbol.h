//
//  Symbol.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__Symbol_h
#define pgf__Symbol_h

#include <string>

#include <gf/RefBase.h>

namespace gf {
    namespace reader {
        
        class Symbol : public gf::RefBase {
        private:
            
        public:
            Symbol();
            virtual ~Symbol();
            
            virtual std::string toString() const = 0;
        };
        
    }
}

#endif
