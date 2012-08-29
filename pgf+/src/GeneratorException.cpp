//
//  GeneratorException.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/GeneratorException.h>

namespace gf {
    
    GeneratorException::GeneratorException() {
    }
    
    GeneratorException::GeneratorException(const std::string& message)
        : Exception(message) {
    }
    
    GeneratorException::~GeneratorException() throw() {
    }
    
}

