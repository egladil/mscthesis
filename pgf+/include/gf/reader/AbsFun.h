//
//  AbsFun.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__AbsFun_h
#define pgf__AbsFun_h

#include <string>
#include <vector>

#include <gf/RefBase.h>
#include <gf/reader/Eq.h>
#include <gf/reader/Type.h>

namespace gf {
    namespace reader {
        
        class AbsFun : public gf::RefBase {
        private:
            /* final */ std::string name;
            /* final */ Type* type;
            /* final */ int32_t arity;
            /* final */ std::vector<Eq*> eqs;
            /* final */ double weight;
            
        public:
            /**
             * Create an AbsFun object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            AbsFun(const std::string& name, Type* type, int32_t arity, const std::vector<Eq*>& eqs, double weight);
            virtual ~AbsFun();
            
            virtual const std::string& getName() const;
            virtual Type* getType() const;
            virtual int32_t getArity() const;
            virtual const std::vector<Eq*>& getEqs() const;
            virtual double getWeight() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
