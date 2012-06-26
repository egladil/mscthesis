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
            /**
             * Create a VarAsPattern object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            VarAsPattern(const std::string& name, Pattern* pattern);
            virtual ~VarAsPattern();
            
            virtual const std::string& getName() const;
            virtual Pattern* getPattern() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
