//
//  IntLit.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__IntLit_h
#define pgf__IntLit_h

#include <stdint.h>
#include <gf/reader/RLiteral.h>

namespace gf {
    namespace reader {
        
        class IntLit : public RLiteral {
        private:
            int32_t value;
            
        public:
            IntLit(int32_t value);
            virtual ~IntLit();
            
            virtual std::string toString() const;
            
            virtual int32_t getValue() const;
            
        };
        
    }
}

#endif
