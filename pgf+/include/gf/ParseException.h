//
//  ParseException.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _ParseException_h
#define _ParseException_h

#include <gf/Exception.h>

namespace gf {
    
    class ParseException : public Exception {
    private:
        
    public:
        ParseException();
        ParseException(const std::string& message);
        virtual ~ParseException() throw();
    };
    
}


#endif
