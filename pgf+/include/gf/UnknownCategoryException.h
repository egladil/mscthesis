//
//  UnknownCategoryException.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef pgf__UnknownCategoryException_h
#define pgf__UnknownCategoryException_h

#include <string>

#include <gf/Exception.h>

namespace gf {
    
    class UnknownCategoryException : public Exception {
    private:
        std::string category;
        
    public:
        UnknownCategoryException(const std::string& category);
        virtual ~UnknownCategoryException();
        
        virtual const std::string& getCategory() const;
    };
    
}


#endif
