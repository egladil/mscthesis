//
//  LeafKP.h
//  
//
//  Created by Emil Djupfeldt on 2012-06-28.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _LeafKP_h
#define _LeafKP_h

#include <string>
#include <vector>

#include <gf/linearizer/BracketedToken.h>
#include <gf/reader/Alternative.h>

namespace gf {
    namespace linearizer {
        
        class LeafKP : public BracketedToken {
        private:
            std::vector<std::string> tokens;
            std::vector<gf::reader::Alternative*> alternatives;
            
        public:
            LeafKP(const std::vector<std::string>& tokens, const std::vector<gf::reader::Alternative*>& alternatives);
            virtual ~LeafKP();
            
            virtual const std::vector<std::string>& getTokens() const;
            virtual const std::vector<gf::reader::Alternative*>& getAlternatives() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
