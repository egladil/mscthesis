//
//  AbsNameExp.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/AbsNameExp.h>

namespace gf {
    namespace reader {
        
        AbsNameExp::AbsNameExp(const std::string& name)
            : name(name) {
        }
        
        AbsNameExp::~AbsNameExp() {
        }
        
        const std::string& AbsNameExp::getName() const {
            return name;
        }
        
        std::string AbsNameExp::toString() const {
            return "Abstract name expression: [name: " + name + "]";
        }
        
    }
}