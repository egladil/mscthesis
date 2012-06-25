//
//  Hypo.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__Hypo_h
#define pgf__Hypo_h

#include <string>

#include <gf/RefBase.h>
#include <gf/reader/Type.h>

namespace gf {
    namespace reader {
        class Type;
        
        class Hypo : public gf::RefBase {
        private:
            /* final */ bool bind;
            /* final */ std::string name;
            /* final */ Type* type;
            
        public:
            /**
             * Create a Hypo object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            Hypo(bool bind, const std::string& str, Type* type);
            virtual ~Hypo();
            
            virtual std::string toString() const;
            
            virtual bool getBind() const;
            virtual const std::string& getName() const;
            virtual const Type& getType() const;
        };
        
    }
}

#endif
