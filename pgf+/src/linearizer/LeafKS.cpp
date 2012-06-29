//
//  LeafKS.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-29.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/linearizer/LeafKS.h>

namespace gf {
    namespace linearizer {
        
        LeafKS::LeafKS(const std::vector<std::string>& tokens)
            : tokens(tokens) {
        }
        
        LeafKS::~LeafKS() {
        }
        
        const std::vector<std::string>& LeafKS::getTokens() const {
            return tokens;
        }
        
        std::string LeafKS::toString() const {
            return '"' + gf::merge(tokens, " ") + '"';
        }
    }
}