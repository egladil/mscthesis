//
//  Bracket.h
//  
//
//  Created by Emil Djupfeldt on 2012-06-28.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _Bracket_h
#define _Bracket_h

#include <stdint.h>
#include <string>
#include <vector>

#include <gf/linearizer/BracketedToken.h>

namespace gf {
    namespace linearizer {
        
        class Bracket : public BracketedToken {
        private:
            std::string cId;
            uint32_t lIndex;
            uint32_t fId;
            std::vector<BracketedToken*> tokens;
            
        public:
            Bracket(const std::string& cId, uint32_t lIndex, uint32_t fId, const std::vector<BracketedToken*>& tokens);
            virtual ~Bracket();
            
            virtual const std::string& getCId() const;
            virtual uint32_t getLIndex() const;
            virtual uint32_t getFId() const;
            virtual const std::vector<BracketedToken*> getBracketedTokens() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
