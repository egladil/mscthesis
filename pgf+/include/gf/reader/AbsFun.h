//
//  AbsFun.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef pgf__AbsFun_h
#define pgf__AbsFun_h

#include <string>
#include <vector>

#include <gf/reader/Eq.h>
#include <gf/reader/Type.h>

namespace gf {
    namespace reader {
        
        class AbsFun {
        private:
            /* final */ std::string name;
            /* final */ Type type;
            /* final */ int32_t arity;
            /* final */ std::vector<Eq> eqs;
            /* final */ double weight;
            
        public:
            AbsFun(const std::string& name, const Type& type, int32_t arity, const std::vector<Eq>& eqs, double weight);
            virtual ~AbsFun();
            
            virtual const std::string& name() const;
            virtual const Type& type() const;
            virtual int32_t arity() const;
            virtual const std::vectorEq> eqs() const;
            virtual double weight() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
