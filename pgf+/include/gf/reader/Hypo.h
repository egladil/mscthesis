//
//  Hypo.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef pgf__Hypo_h
#define pgf__Hypo_h

#include <string>

#include <gf/reader/Type.h>

namespace gf {
    namespace reader {
        
        class Hypo {
        private:
            /* final */ bool bind;
            /* final */ std::string name;
            /* final */ Type type;
            
        public:
            Hypo(bool bind, const std::string& str, const Type& type);
            virtual ~Hypo();
            
            virtual std::string toString() const;
            
            virtual bool getBind() const;
            virtual const std::string& getName() const;
            virtual const Type& getType() const;
        };
        
    }
}

#endif
