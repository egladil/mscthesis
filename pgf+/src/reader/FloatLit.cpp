//
//  FloatLit.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/reader/FloatLit.h>

namespace gf {
    namespace reader {
        
        FloatLit::FloatLit(double value)
            : value(value) {
        }
        
        FloatLit::~FloatLit() {
        }
        
        std::string FloatLit::toString() const {
            return "Float literal: " + gf::toString(value);
        }
        
        double FloatLit::getValue() const {
            return value;
        }
        
    }
}