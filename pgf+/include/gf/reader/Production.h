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
#include <set>
#include <string>
#include <vector>

#include <gf/RefBase.h>

namespace gf {
    namespace reader {
        
        class Production : public gf::RefBase {
        private:
            uint32_t selector;
            
        protected:
            uint32_t fId;
            
        public:
            Production(uint32_t selector, uint32_t fId);
            virtual ~Production();
            
            virtual uint32_t getCategory() const;
            
            virtual uint32_t getRange() const;
            
            virtual std::string toString() const = 0;
            virtual bool operator < (const Production* other) const = 0;
            
            virtual const std::vector<uint32_t>& getDomain() const = 0;
            
            virtual uint32_t getSelector() const;
            virtual uint32_t getFId() const;
        };
        
        class ProductionContentComparator {
        public:
            inline bool operator()(const Production* a, const Production* b) {
                return a->operator<(b);
            }
        };
        
        typedef std::set<Production*> ProductionPointerSet;
        typedef std::set<Production*, ProductionContentComparator> ProductionContentSet;
        
    }
}

#endif
