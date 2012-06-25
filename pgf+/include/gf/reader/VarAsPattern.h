//
//  VarAsPattern.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__VarAsPattern_h
#define pgf__VarAsPattern_h

#include <string>
#include <gf/reader/Pattern.h>

namespace gf {
    namespace reader {
        
        class VarAsPattern : public Pattern {
        private:
            std::string name;
            Pattern* pattern;
            
        public:
            VarAsPattern(const std::string& name, Pattern* pattern);
            
            virtual const std::string& getName() const;
            virtual Pattern* getPattern() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
