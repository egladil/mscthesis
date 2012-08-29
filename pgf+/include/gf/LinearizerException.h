//
//  LinearizerException.h
//  
//
//  Created by Emil Djupfeldt on 2012-06-28.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _LinearizerException_h
#define _LinearizerException_h

#include <gf/Exception.h>

namespace gf {
    
    class LinearizerException : public Exception {
    private:
        
    public:
        LinearizerException();
        LinearizerException(const std::string& message);
        virtual ~LinearizerException() throw();
    };
    
}

#endif
