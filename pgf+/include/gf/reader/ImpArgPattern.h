//
//  ImpArgPattern.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__ImpArgPattern_h
#define pgf__ImpArgPattern_h

#include <gf/reader/Pattern.h>

namespace gf {
    namespace reader {
        
        class ImpArgPattern : public Pattern {
        private:
            Pattern* name;
            
        public:
            ImpArgPattern(Pattern* name);
            virtual ~ImpArgPattern();
            
            virtual Pattern* getName() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
