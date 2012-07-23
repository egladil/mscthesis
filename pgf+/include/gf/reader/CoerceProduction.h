//
//  CoerceProduction.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__CoerceProduction_h
#define pgf__CoerceProduction_h

#include <stdint.h>
#include <vector>
#include <gf/reader/Production.h>

namespace gf {
    namespace reader {
        
        class CoerceProduction : public Production {
        private:
            uint32_t initId;
            std::vector<uint32_t> domain;
            
        public:
            CoerceProduction(uint32_t fId, uint32_t initId);
            virtual ~CoerceProduction();
            
            virtual std::string toString() const;
            virtual bool operator < (const Production* other) const;
            
            virtual const std::vector<uint32_t>& getDomain() const;
            
            virtual uint32_t getInitId() const;
        };
        
    }
}

#endif
