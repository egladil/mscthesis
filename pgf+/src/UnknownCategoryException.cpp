//
//  UnknownCategoryException.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/UnknownCategoryException.h>

namespace gf {
    
    UnknownCategoryException::UnknownCategoryException(const std::string& message)
    : Exception(message) {
    }
    
    UnknownCategoryException::~UnknownCategoryException() {
    }
    
}
