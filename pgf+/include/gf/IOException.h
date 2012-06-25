//
//  IOException.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__IOException_h
#define pgf__IOException_h

#include <gf/Exception.h>

namespace gf {
    
    class IOException : public Exception {
    private:
        
    public:
        IOException();
        IOException(const std::string& message);
        virtual ~IOException();
    };
    
}

#endif
