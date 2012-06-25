//
//  AppPattern.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__AppPattern_h
#define pgf__AppPattern_h

#include <string>
#include <vector>
#include <gf/reader/Pattern.h>

namespace gf {
    namespace reader {
        
        class AppPattern : public Pattern {
        private:
            std::string name;
            std::vector<Pattern*> patterns;
            
        public:
            AppPattern(const std::string& name, const std::vector<Pattern*>& patterns);
            virtual ~AppPattern();
            
            virtual const std::string& getName() const;
            virtual const std::vector<Pattern*> getPatterns() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
