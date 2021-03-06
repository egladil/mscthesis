//
//  UnknownLanguageException.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__UnknownLanguageException_h
#define pgf__UnknownLanguageException_h

#include <gf/Exception.h>

namespace gf {
    
    class UnknownLanguageException : public Exception {
    private:
        std::string language;
        
    public:
        UnknownLanguageException(const std::string& language);
        virtual ~UnknownLanguageException() throw();
        
        virtual const std::string& getLanguage() const;
    };
    
}


#endif
