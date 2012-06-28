//
//  LeafKS.h
//  
//
//  Created by Emil Djupfeldt on 2012-06-28.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _LeafKS_h
#define _LeafKS_h

#include <string>
#include <vector>

#include <gf/linearizer/BracketedToken.h>

namespace gf {
    namespace linearizer {
        
        class LeafKS : public BracketedToken {
        private:
            std::vector<std::string> tokens;
            
        public:
            LeafKS(const std::vector<std::string>& tokens);
            virtual ~LeafKS();
            
            virtual const std::vector<std::string>& getTokens() const;
            
            virtual std::string toString() const;
        };

        
    }
}

#endif
