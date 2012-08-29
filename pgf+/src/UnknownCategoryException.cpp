//
//  UnknownCategoryException.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/UnknownCategoryException.h>

namespace gf {
    
    UnknownCategoryException::UnknownCategoryException(const std::string& category)
        : Exception("Unknown category: " + category), category(category) {
    }
    
    UnknownCategoryException::~UnknownCategoryException() throw() {
    }
    
    const std::string& UnknownCategoryException::getCategory() const {
        return category;
    }
}
