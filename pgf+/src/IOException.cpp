//
//  IOException.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <string.h>
#include <gf/IOException.h>

namespace gf {
    
    IOException::IOException() {
    }
    
    IOException::IOException(const std::string& message)
        : Exception(message) {
    }
    
    
    IOException::IOException(int err)
        : Exception(strerror(err)) {
    }
    
    IOException::~IOException() throw() {
    }
    
}
