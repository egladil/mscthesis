//
//  ParseException.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/ParseException.h>

namespace gf {
    
    ParseException::ParseException() {
    }
    
    ParseException::ParseException(const std::string& message)
        : Exception(message) {
    }
    
    ParseException::~ParseException() {
    }
    
}