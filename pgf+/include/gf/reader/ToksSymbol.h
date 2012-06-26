//
//  ToksSymbol.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__ToksSymbol_h
#define pgf__ToksSymbol_h

#include <string>
#include <vector>
#include <gf/reader/Symbol.h>

namespace gf {
    namespace reader {
        
        class ToksSymbol : public Symbol {
        private:
            std::vector<std::string> tokens;
            
        public:
            ToksSymbol(const std::vector<std::string>& tokens);
            virtual ~ToksSymbol();
            
            virtual const std::vector<std::string>& getTokens() const;
            
            virtual bool isTerminal() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
