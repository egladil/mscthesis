//
//  IMMetaVariable.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _IMMetaVariable_h
#define _IMMetaVariable_h

#include <stdint.h>
#include <gf/parser/IMTree.h>

namespace gf {
    namespace parser {
        
        class IMMetaVariable : IMTree {
        private:
            uint32_t id;
            
        public:
            IMMetaVariable(uint32_t id);
            virtual ~IMMetaVariable();
            
            virtual uint32_t getId() const;
            
            virtual gf::Tree* toAbstract() const;
        };
        
    }
}

#endif
