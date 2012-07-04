//
//  IMVariable.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _IMVariable_h
#define _IMVariable_h

#include <string>
#include <gf/parser/IMTree.h>

namespace gf {
    namespace parser {
        
        class IMVariable : IMTree {
        private:
            std::string cId;
            
        public:
            IMVariable(const std::string& cId);
            virtual ~IMVariable();
            
            virtual const std::string& getCId() const;
        };
        
    }
}

#endif
