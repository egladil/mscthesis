//
//  ToksSymbol.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/ToksSymbol.h>

namespace gf {
    namespace reader {
        
        ToksSymbol::ToksSymbol(const std::vector<std::string>& tokens)
            : tokens(tokens) {
        }
        
        ToksSymbol::~ToksSymbol() {
        }
        
        const std::vector<std::string>& ToksSymbol::getTokens() const {
            return tokens;
        }
        
        bool ToksSymbol::isTerminal() const {
            return true;
        }
        
        std::string ToksSymbol::toString() const {
            std::string ret;
            
            ret = "Tokens:";
            for (std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); it++) {
                ret+= *it;
            }
            
            return ret;
        }
        
    }
}