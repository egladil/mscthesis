//
//  Hypo.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/Hypo.h>

namespace gf {
    namespace reader {
        
        Hypo::Hypo(bool bind, const std::string& name, Type* type)
        : bind(bind), name(name), type(type) {
        }
        
        Hypo::~Hypo() {
            gf::release(type);
        }
        
        std::string Hypo::toString() const {
            if (bind) {
                return "(" + name + ": " + type->toString() + ")";
            } else {
                return type->toString();
            }
        }
        
        bool Hypo::getBind() const {
            return bind;
        }
        
        const std::string& Hypo::getName() const {
            return name;
        }
        
        const Type* Hypo::getType() const {
            return type;
        }
        
    }
}