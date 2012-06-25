//
//  ArgConstSymbol.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__ArgConstSymbol_h
#define pgf__ArgConstSymbol_h

#include <stdint.h>
#include <gf/reader/Symbol.h>

namespace gf {
    namespace reader {
        
        class ArgConstSymbol : public Symbol {
        private:
            int32_t arg;
            int32_t cons;
            
        public:
            ArgConstSymbol(int32_t arg, int32_t cons);
            virtual ~ArgConstSymbol();
            
            virtual int32_t getArg() const;
            virtual int32_t getCons() const;
            
            virtual std::string toString() const;
        };
        
    }
}


#endif
