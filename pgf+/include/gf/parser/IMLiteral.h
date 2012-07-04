//
//  IMLiteral.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _IMLiteral_h
#define _IMLiteral_h

#include <string>
#include <gf/parser/IMTree.h>

namespace gf {
    namespace parser {
        
        class IMLiteral : public IMTree {
        private:
            std::string value;
            
        public:
            IMLiteral(const std::string& value);
            virtual ~IMLiteral();
            
            virtual const std::string& getValue() const;
            
            virtual gf::Tree* toAbstract() const;
        };
        
    }
}

#endif
