//
//  Sequence.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__Sequence_h
#define pgf__Sequence_h

#include <stdint.h>
#include <string>
#include <vector>

#include <gf/RefBase.h>
#include <gf/reader/Symbol.h>

namespace gf {
    namespace reader {
        
        class Sequence : public gf::RefBase {
        private:
            std::vector<Symbol*> symbols;
            
        public:
            /**
             * Create a Sequence object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference.
             */
            Sequence(const std::vector<Symbol*>& symbols);
            virtual ~Sequence();
            
            virtual const std::vector<Symbol*>& getSymbols() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
