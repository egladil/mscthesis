//
//  VarPattern.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__VarPattern_h
#define pgf__VarPattern_h

#include <string>
#include <gf/reader/Pattern.h>

namespace gf {
    namespace reader {
        
        class VarPattern : public Pattern {
        private:
            std::string name;
            
        public:
            VarPattern(const std::string& name);
            virtual ~VarPattern();
            
            virtual const std::string& getName() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
