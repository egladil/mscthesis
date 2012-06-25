//
//  Exception.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__Exception_h
#define pgf__Exception_h

#include <string>

namespace gf {
    
    class Exception {
    private:
        std::string message;
        
    public:
        Exception();
        Exception(const std::string& message);
        virtual ~Exception();
        
        virtual const std::string& getMessage() const;
        
        virtual std::string toString() const;
    };
    
}

#endif
