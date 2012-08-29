//
//  MetaExp.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__MetaExp_h
#define pgf__MetaExp_h

#include <stdint.h>
#include <gf/reader/Expr.h>

namespace gf {
    namespace reader {
        
        class MetaExp : public Expr {
        private:
            int32_t id;
            
        public:
            MetaExp(int32_t id);
            virtual ~MetaExp();
            
            virtual int32_t getMeta() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
