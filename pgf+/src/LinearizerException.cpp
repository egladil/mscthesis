//
//  LinearizerException.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-29.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/LinearizerException.h>

namespace gf {
    
    LinearizerException::LinearizerException() {
    }
    
    LinearizerException::LinearizerException(const std::string& message)
        : Exception(message) {
    }
    
    LinearizerException::~LinearizerException() {
    }
    
}
