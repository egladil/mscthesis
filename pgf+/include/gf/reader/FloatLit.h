//
//  FloatLit.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__FloatLit_h
#define pgf__FloatLit_h

#include <gf/reader/RLiteral.h>

namespace gf {
    namespace reader {
        
        class FloatLit : public RLiteral {
        private:
            double value;
            
        public:
            FloatLit(double value);
            virtual ~FloatLit();
            
            virtual std::string toString() const;
            
            virtual double getValue() const;
            
        };
        
    }
}

#endif
