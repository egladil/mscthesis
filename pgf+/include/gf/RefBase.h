//
//  RefBase.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__RefBase_h
#define pgf__RefBase_h

#include <string>

namespace gf {
    
    class RefBase {
    private:
        int referenceCounter;
        
    public:
        RefBase();
        virtual ~RefBase();
        
        virtual void addReference();
        virtual void release();
        
        virtual std::string toString() const;
    };
    
    static inline void release(RefBase*& ptr) {
        if (ptr != NULL) {
            ptr->release();
            ptr = NULL;
        }
    }
    
}


#endif
