//
//  RezDesc.h
//  
//
//  Created by Emil Djupfeldt on 2012-06-28.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _RezDesc_h
#define _RezDesc_h

#include <stdint.h>
#include <vector>

#include <gf/RefBase.h>
#include <gf/linearizer/BracketedToken.h>
#include <gf/linearizer/CncType.h>

namespace gf {
    namespace linearizer {
        
        class RezDesc : public RefBase {
        private:
            uint32_t fId;
            std::vector<CncType*> cncTypes;
            std::vector<std::vector<std::vector<BracketedToken*> > > tokens;
            
        public:
            RezDesc(uint32_t fId, const std::vector<CncType*>& cncTypes, const std::vector<std::vector<std::vector<BracketedToken*> > >& tokens);
            virtual ~RezDesc();
            
            virtual uint32_t getFId() const;
            virtual const std::vector<CncType*>& getConcreteTypes() const;
            virtual const std::vector<std::vector<std::vector<BracketedToken*> > >& getBracketedTokens() const;
        };
        
    }
}

#endif
