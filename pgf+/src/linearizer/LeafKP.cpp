//
//  LeafKP.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-29.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/linearizer/LeafKP.h>

namespace gf {
    namespace linearizer {
        
        LeafKP::LeafKP(const std::vector<std::string>& tokens, const std::vector<gf::reader::Alternative*>& alternatives)
            : tokens(tokens), alternatives(alternatives) {
        }
        
        LeafKP::~LeafKP() {
            for (std::vector<gf::reader::Alternative*>::iterator it = alternatives.begin(); it != alternatives.end(); it++) {
                gf::release(*it);
            }
        }
        
        const std::vector<std::string>& LeafKP::getTokens() const {
            return tokens;
        }
        
        const std::vector<gf::reader::Alternative*>& LeafKP::getAlternatives() const {
            return alternatives;
        }
        
        std::string LeafKP::toString() const {
            std::string ret;
            
            ret = "string names: [";
            for (std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); it++) {
                ret+= (it == tokens.begin() ? "" : " ") + *it;
            }
            ret+= "], alternatives: [";
            for (std::vector<gf::reader::Alternative*>::const_iterator it = alternatives.begin(); it != alternatives.end(); it++) {
                ret+= (it == alternatives.begin() ? "" : " ") + (*it)->toString();
            }
            ret+= "]";
            
            return ret;
        }
        
    }
}