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

#include <gf/reader/Symbol.h>

namespace gf {
    namespace reader {
        
        class Sequence {
        private:
            std::vector<Symbol> symbs;
            
        public:
            Sequence(const std::vector<Symbol> symbs);
            virtual ~Sequence();
            
            virtual Symbol& symbol(uint32_t index);
            virtual const Symbol& symbol(uint32_t index) const;
            
            virtual uint32_t length() const;
            
            virtual const std::vector<Symbol> getSymbols() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
