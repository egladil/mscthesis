//
//  UnknownLanguageException.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/UnknownLanguageException.h>

namespace gf {
    
    UnknownLanguageException::UnknownLanguageException(const std::string& message)
    : Exception(message) {
    }
    
    UnknownLanguageException::~UnknownLanguageException() {
    }
    
}
