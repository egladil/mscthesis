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

namespace gf {
    namespace reader {
        
        class Production {
        private:
            int32_t sel;
            
        protected:
            int32_t fId;
            
        public:
            Production(int32_t selector, int32_t fId);
            virtual ~Production();
            
            virtual int32_t getCategory() const;
            
            virtual int32_t range() const;
            
            virtual std::string toString() const = 0;
            
            virtual const std::vector<int32_t>& domain() const;
            
            virtual int32_t getSel() const;
            virtual int32_t getFId() const;
        };
        
    }
}

#endif
