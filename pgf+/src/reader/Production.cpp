//
//  Production.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/Production.h>

namespace gf {
    namespace reader {
        
        Production::Production(uint32_t selector, uint32_t fId)
        : selector(selector), fId(fId) {
        }
        
        Production::~Production() {
        }
        
        uint32_t Production::getCategory() const {
            return fId;
        }
        
        uint32_t Production::getRange() const {
            return fId;
        }
        
        uint32_t Production::getSelector() const {
            return selector;
        }
        
        uint32_t Production::getFId() const {
            return fId;
        }
        
    }
}