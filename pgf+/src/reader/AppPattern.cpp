//
//  AppPattern.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/AppPattern.h>

namespace gf {
    namespace reader {
        
        AppPattern::AppPattern(const std::string& name, const std::vector<Pattern*>& patterns)
            : name(name), patterns(patterns) {
        }
        
        AppPattern::~AppPattern() {
            for (std::vector<Pattern*>::iterator it = patterns.begin(); it != patterns.end(); it++) {
                gf::release(*it);
            }
        }
        
        const std::string& AppPattern::getName() const {
            return name;
        }
        
        const std::vector<Pattern*> AppPattern::getPatterns() const {
            return patterns;
        }
        
        std::string AppPattern::toString() const {
            std::string ret;
            
            ret = "Application pattern [name: ";
            ret+= name;
            ret+= ", patterns: (";
            for (std::vector<Pattern*>::const_iterator it = patterns.begin(); it != patterns.end(); it++) {
                ret+= (it == patterns.begin() ? "" : " ") + (*it)->toString();
            }
            ret+= ")";
            
            return ret;
        }
        
    }
}