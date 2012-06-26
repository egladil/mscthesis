//
//  WeightedIdent.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/WeightedIdent.h>

namespace gf {
    namespace reader {
        
        WeightedIdent::WeightedIdent(const std::string& ident, double weight)
        : ident(ident), weight(weight) {
        }
        
        WeightedIdent::~WeightedIdent() {
        }
        
        const std::string& WeightedIdent::getIdent() const {
            return ident;
        }
        
        double WeightedIdent::getWeight() const {
            return weight;
        }
        
    }
}