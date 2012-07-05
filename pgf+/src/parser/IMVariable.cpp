//
//  IMVariable.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-05.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/parser/IMVariable.h>

namespace gf {
    namespace parser {
        
        
        IMVariable::IMVariable(const std::string& cId)
            : cId(cId) {
        }
        
        IMVariable::~IMVariable() {
        }
        
        gf::Tree* IMVariable::toAbstract(const std::vector<std::string>& args) const {
            for (uint32_t i = 0; i < args.size(); i++) {
                if (args.at(i) == cId) {
                    return new gf::Variable(i);
                }
            }
            
            // TODO: Same behaviour as in scala code. But wouldn't an exception be better?
            return new gf::Variable(-1);
        }
        
        const std::string& IMVariable::getCId() const {
            return cId;
        }
        
    }
}
