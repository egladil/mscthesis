//
//  MetaExp.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/reader/MetaExp.h>

namespace gf {
    namespace reader {
        
        MetaExp::MetaExp(int32_t id)
            : id(id) {
        }
        
        MetaExp::~MetaExp() {
        }
        
        int32_t MetaExp::getMeta() const {
            return id;
        }
        
        std::string MetaExp::toString() const {
            return "Meta expression: [" + gf::toString(id) + "]";
        }
        
    }
}