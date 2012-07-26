//
//  GeneratorException.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-26.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _GeneratorException_h
#define _GeneratorException_h

#include <gf/Exception.h>

namespace gf {
    
    class GeneratorException : public Exception {
    private:
        
    public:
        GeneratorException();
        GeneratorException(const std::string& message);
        virtual ~GeneratorException();
    };
    
}

#endif
