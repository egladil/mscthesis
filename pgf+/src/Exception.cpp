//
//  Exception.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <typeinfo>
#include <gf/Exception.h>

namespace gf {
    
    Exception::Exception() {
    }
    
    Exception::Exception(const std::string& message)
        : message(message) {
    }
    
    Exception::~Exception() throw() {
    }
    
    const std::string& Exception::getMessage() const {
        return message;
    }
    
    std::string Exception::toString() const {
        std::string ret;
        
        ret = this == NULL ? "null" : typeid(*this).name();
        ret+= ": ";
        ret+= message;
        
        return ret;
    }
    
    const char* Exception::what() const throw() {
    	return message.c_str();
    }
}

