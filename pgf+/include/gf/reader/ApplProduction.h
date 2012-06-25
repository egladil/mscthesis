//
//  ApplProduction.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__ApplProduction_h
#define pgf__ApplProduction_h

#include <stdint.h>
#include <vector>
#include <gf/reader/CncFun.h>
#include <gf/reader/Production.h>

namespace gf {
    namespace reader {
        
        class ApplProduction : public Production {
        private:
            /* final */ CncFun* function;
            /* final */ std::vector<uint32_t> domain;
            
        public:
            /**
             * Create an ApplProduction object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            ApplProduction(uint32_t fId, CncFun* function, const std::vector<uint32_t>& domain);
            virtual ~ApplProduction();
            
            virtual std::string toString() const;
            virtual bool equals(const Production* other) const;
            
            virtual const std::vector<uint32_t>& getDomain() const;
            
            virtual CncFun* getFunction() const;
            
            virtual const std::vector<uint32_t>& getArgs() const;
        };
        
    }
}

#endif
