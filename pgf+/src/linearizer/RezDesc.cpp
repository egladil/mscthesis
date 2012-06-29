//
//  RezDesc.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-29.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/linearizer/RezDesc.h>

namespace gf {
    namespace linearizer {
        
        RezDesc::RezDesc(uint32_t fId, const std::vector<CncType*>& cncTypes, const std::vector<std::vector<std::vector<BracketedToken*> > >& tokens)
            : fId(fId), cncTypes(cncTypes), tokens(tokens) {
        }
        
        RezDesc::~RezDesc() {
            for (std::vector<CncType*>::iterator it = cncTypes.begin(); it != cncTypes.end(); it++) {
                gf::release(*it);
            }
            for (std::vector<std::vector<std::vector<BracketedToken*> > >::iterator it = tokens.begin(); it != tokens.end(); it++) {
                for (std::vector<std::vector<BracketedToken*> >::iterator it2 = it->begin(); it2 != it->end(); it2++) {
                    for (std::vector<BracketedToken*>::iterator it3 = it2->begin(); it3 != it2->end(); it3++) {
                        gf::release(*it3);
                    }
                }
            }
        }
        
        uint32_t RezDesc::getFId() const {
            return fId;
        }
        
        const std::vector<CncType*>& RezDesc::getConcreteTypes() const {
            return cncTypes;
        }
        
        const std::vector<std::vector<std::vector<BracketedToken*> > >& RezDesc::getBracketedTokens() const {
            return tokens;
        }
        
    }
}