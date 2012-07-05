//
//  IMLiteral.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-05.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/parser/IMLiteral.h>

namespace gf {
    namespace parser {
        
        IMLiteral::IMLiteral(const std::string& value)
            : value(value) {
        }
        
        IMLiteral::~IMLiteral() {
        }
        
        gf::Tree* IMLiteral::toAbstract(const std::vector<std::string>& args) const {
            return new gf::Literal(new gf::StringLiteral(value));
        }
        
        const std::string& IMLiteral::getValue() const {
            return value;
        }
        
    }
}
