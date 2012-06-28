//
//  LinTriple.h
//  
//
//  Created by Emil Djupfeldt on 2012-06-28.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _LinTriple_h
#define _LinTriple_h

#include <stdint.h>
#include <string>
#include <vector>

#include <gf/RefBase.h>
#include <gf/linearizer/BracketedToken.h>
#include <gf/linearizer/CncType.h>

namespace gf {
    namespace linearizer {
        
        class LinTriple : public RefBase {
        private:
            uint32_t fId;
            CncType* cncType;
            std::vector<std::vector<BracketedToken*> > linTable;
            
        public:
            LinTriple(uint32_t fId, CncType* cncType, const std::vector<std::vector<BracketedToken*> >& linTable);
            virtual ~LinTriple();
            
            virtual uint32_t getFId() const;
            virtual CncType* getConcreteType() const;
            virtual const std::vector<std::vector<BracketedToken*> >& getLinTable() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
