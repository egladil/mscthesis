//
//  Alternative.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/Alternative.h>

namespace gf {
    namespace reader {
        
        Alternative::Alternative(const std::vector<std::string>& tokens, const std::vector<std::string>& prefix)
            : tokens(tokens), prefix(prefix) {
        }
        
        Alternative::~Alternative() {
        }
        
        const std::vector<std::string>& Alternative::getAlt1() const {
            return tokens;
        }
        
        const std::vector<std::string>& Alternative::getAlt2() const {
            return prefix;
        }
        
        std::string Alternative::toString() const {
            std::string ret;
            
            for (std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); it++) {
                ret+= *it + " ";
            }
            
            ret+= "/";
            
            for (std::vector<std::string>::const_iterator it = prefix.begin(); it != prefix.end(); it++) {
                ret+= " " + *it;
            }
            
            return ret;
        }
        
    }
}