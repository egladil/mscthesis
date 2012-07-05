//
//  IMMetaVariable.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-05.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/parser/IMMetaVariable.h>

namespace gf {
    namespace parser {
        
        IMMetaVariable::IMMetaVariable(uint32_t id)
            : id(id) {
        }
        
        IMMetaVariable::~IMMetaVariable() {
        }
        
        gf::Tree* IMMetaVariable::toAbstract(const std::vector<std::string>& args) const {
            return new gf::MetaVariable(id);
        }
        
        uint32_t IMMetaVariable::getId() const {
            return id;
        }
        
    }
}
