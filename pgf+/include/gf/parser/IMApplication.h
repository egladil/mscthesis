//
//  IMApplication.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _IMApplication_h
#define _IMApplication_h

#include <string>
#include <vector>
#include <gf/parser/IMTree.h>

namespace gf {
    namespace parser {
        
        class IMApplication : IMTree {
        private:
            std::string fun;
            std::vector<IMTree*> args;
            
        public:
            IMApplication(const std::string& fun, const std::vector<IMTree*>& args);
            virtual ~IMApplication();
            
            virtual const std::string& getFunction() const;
            virtual const std::vector<IMTree*>& getArguments() const;
        };
        
    }
}

#endif
