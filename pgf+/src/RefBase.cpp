//
//  RefBase.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <stdint.h>
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
#ifdef DEBUG
        fprintf(stderr, "releasing %s with ref count %i\n", RefBase::toString().c_str(), referenceCounter);
#endif
        referenceCounter--;
        if (referenceCounter <= 0) {
            delete this;
        }
    }
    
#ifdef DEBUG
    int RefBase::getReferenceCount() const {
        return referenceCounter;
    }
#endif
    
    std::string RefBase::toString() const {
        std::string ret;
        char buf[32];
        
        if (this == NULL) {
            return "null";   // Should not happen.
        }
        
        ret = typeid(*this).name();
        ret+= "@";
        
        snprintf(buf, sizeof(buf) - 1, "0x%16.16llx", (uint64_t) this);
        buf[sizeof(buf) - 1] = 0;
        
        ret+= buf;
        
        return ret;
    }
    
}
