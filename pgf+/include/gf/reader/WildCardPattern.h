//
//  WildCardPattern.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__WildCardPattern_h
#define pgf__WildCardPattern_h

#include <gf/reader/Pattern.h>

namespace gf {
    namespace reader {
        
        class WildCardPattern : public Pattern {
        private:
            
        public:
            WildCardPattern();
            virtual ~WildCardPattern();
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
