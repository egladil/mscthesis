//
//  Alternative.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__Alternative_h
#define pgf__Alternative_h

#include <string>
#include <vector>

#include <gf/RefBase.h>

namespace gf {
    namespace reader {
        
        class Alternative : public gf::RefBase {
        private:
            std::vector<std::string> tokens;
            std::vector<std::string> prefix;
            
        public:
            Alternative(const std::vector<std::string>& tokens, const std::vector<std::string>& prefix);
            virtual ~Alternative();
            
            virtual const std::vector<std::string>& getAlt1() const;
            virtual const std::vector<std::string>& getAlt2() const;
            
            virtual std::string toString() const;
        };
        
    }
}


#endif
