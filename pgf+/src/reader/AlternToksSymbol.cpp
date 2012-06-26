//
//  AlternToksSymbol.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/AlternToksSymbol.h>

namespace gf {
    namespace reader {
        
        AlternToksSymbol::AlternToksSymbol(const std::vector<std::string>& tokens, const std::vector<Alternative*>& alternatives)
            : ToksSymbol(tokens), alternatives(alternatives) {
        }
        
        AlternToksSymbol::~AlternToksSymbol() {
            for (std::vector<Alternative*>::iterator it = alternatives.begin(); it != alternatives.end(); it++) {
                gf::release(*it);
            }
        }
        
        const std::vector<Alternative*>& AlternToksSymbol::getAlternatives() const {
            return alternatives;
        }
        
        std::string AlternToksSymbol::toString() const {
            std::string ret;
            
            ret = "pre {";
            
            for (std::vector<std::string>::const_iterator it = getTokens().begin(); it != getTokens().end(); it++) {
                ret+= (it == getTokens().begin() ? "" : " ") + *it;
            }
            
            for (std::vector<Alternative*>::const_iterator it = alternatives.begin(); it != alternatives.end(); it++) {
                ret+= "; " + (*it)->toString();
            }
            
            ret+= "}";
            
            return ret;
        }
        
    }
}