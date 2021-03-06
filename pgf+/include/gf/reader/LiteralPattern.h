//
//  LiteralPattern.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__LiteralPattern_h
#define pgf__LiteralPattern_h

#include <gf/reader/Pattern.h>
#include <gf/reader/RLiteral.h>

namespace gf {
    namespace reader {
        
        class LiteralPattern : public Pattern {
        private:
            RLiteral* literal;
            
        public:
            /**
             * Create a LiteralPattern object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            LiteralPattern(RLiteral* literal);
            virtual ~LiteralPattern();
            
            virtual RLiteral* getLit() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
