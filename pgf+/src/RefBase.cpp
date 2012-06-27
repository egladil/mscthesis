//
//  RefBase.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <stdio.h>
#include <typeinfo>
#include <gf/RefBase.h>

namespace gf {
    
    RefBase::RefBase()
        : referenceCounter(1) {
    }
    
    RefBase::~RefBase() {
#ifdef DEBUG
        fprintf(stderr, "destroying %s with ref count %i\n", RefBase::toString().c_str(), referenceCounter);
#endif
    }
    
    void RefBase::addReference() {
        referenceCounter++;
    }
    
    void RefBase::release() {
        referenceCounter--;
        if (referenceCounter <= 0) {
            delete this;
        }
    }
    
    std::string RefBase::toString() const {
        if (this == NULL) {
            return "null";   // Should not happen.
        }
        
        return typeid(*this).name();
    }
    
}
