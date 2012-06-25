//
//  ProductionSet.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__ProductionSet_h
#define pgf__ProductionSet_h

#include <stdint.h>
#include <string>
#include <vector>
#include <set>

#include <gf/reader/Production.h>

namespace gf {
    namespace reader {
        
        class ProductionSet {
        private:
            int32_t id;
            std::vector<Production> prods;
            
        public:
            ProductionSet(int32_t id, const std::vector<Production>& prods);
            virtual ~ProductionSet();
            
            virtual uint32_t length() const;
            virtual const std::vector<Production>& getProductions() const;
            
            virtual std::string toString() const;
            
            virtual int32_t getId() const;
            
            // TODO: Cache set?
            virtual std::set<Production> getSetOfProductions() const;
        };
        
    }
}

#endif
