//
//  BracketedToken.h
//  
//
//  Created by Emil Djupfeldt on 2012-06-28.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _BracketedTokn_h
#define _BracketedTokn_h

#include <gf/RefBase.h>

namespace gf {
    namespace linearizer {
        
        class BracketedToken : public RefBase {
        private:
            
        public:
            BracketedToken();
            virtual ~BracketedToken();
            
            virtual std::string toString() const = 0;
        };
        
    }
}

#endif
