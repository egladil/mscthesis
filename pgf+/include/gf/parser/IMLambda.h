//
//  IMLambda.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _IMLambda_h
#define _IMLambda_h

#include <string>
#include <vector>
#include <gf/parser/IMTree.h>

namespace gf {
    namespace parser {
                
        class IMLambda : IMTree {
        private:
            std::vector<std::pair<bool, std::string> > variables;
            IMTree* body;
            
        public:
            /**
             * The list of variables must be non-empty.
             */
            IMLambda(const std::vector<std::pair<bool, std::string> >& variables, IMTree* body);
            virtual ~IMLambda();
            
            virtual const std::vector<std::pair<bool, std::string> >& getVariables() const;
            virtual IMTree* getBody() const;
        };
        
    }
}

#endif
