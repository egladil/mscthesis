//
//  Bracket.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-29.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/linearizer/Bracket.h>

namespace gf {
    namespace linearizer {
        
        Bracket::Bracket(const std::string& cId, uint32_t lIndex, uint32_t fId, const std::vector<BracketedToken*>& tokens)
            : cId(cId), lIndex(lIndex), fId(fId), tokens(tokens) {
        }
        
        Bracket::~Bracket() {
            for (std::vector<BracketedToken*>::iterator it = tokens.begin(); it != tokens.end(); it++) {
                gf::release(*it);
            }
        }
        
        const std::string& Bracket::getCId() const {
            return cId;
        }
        
        uint32_t Bracket::getLIndex() const {
            return lIndex;
        }
        
        uint32_t Bracket::getFId() const {
            return fId;
        }
        
        const std::vector<BracketedToken*>& Bracket::getBracketedTokens() const {
            return tokens;
        }
        
        std::string Bracket::toString() const {
            std::string ret;
            
            ret = "(name: ";
            ret+= cId;
            ret+= ", linindex: ";
            ret+= gf::toString(lIndex);
            ret+= ", fid: ";
            ret+= gf::toString(fId);
            ret+= " [";
            for (std::vector<BracketedToken*>::const_iterator it = tokens.begin(); it != tokens.end(); it++) {
                ret+= (it == tokens.begin() ? "" : ", ") + (*it)->toString();
            }
            ret+= "]";
            
            return ret;
        }
        
    }
}