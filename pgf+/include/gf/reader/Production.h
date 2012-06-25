//
//  Production.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__Production_h
#define pgf__Production_h

#include <stdint.h>
#include <string>
#include <vector>

#include <gf/RefBase.h>

namespace gf {
    namespace reader {
        
        class Production : public gf::RefBase {
        private:
            uint32_t sel;
            
        protected:
            uint32_t fId;
            
        public:
            Production(uint32_t selector, uint32_t fId);
            virtual ~Production();
            
            virtual uint32_t getCategory() const;
            
            virtual uint32_t range() const;
            
            virtual std::string toString() const = 0;
            virtual bool equals(const Production* other) const;
            
            virtual const std::vector<uint32_t>& getDomain() const = 0;
            
            virtual uint32_t getSel() const;
            virtual uint32_t getFId() const;
        };
        
    }
}

#endif
