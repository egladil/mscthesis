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

#include <gf/RefBase.h>
#include <gf/reader/Production.h>

namespace gf {
    namespace reader {
        
        class ProductionSet : public gf::RefBase {
        private:
            uint32_t id;
            std::vector<Production*> productions;
            
        public:
            /**
             * Create a ProductionSet object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            ProductionSet(uint32_t id, const std::vector<Production*>& productions);
            virtual ~ProductionSet();
            
            virtual const std::vector<Production*>& getProductions() const;
            
            virtual std::string toString() const;
            
            virtual uint32_t getId() const;
            
            // TODO: Cache set?
            virtual ProductionPointerSet getSetOfProductions() const;
        };
        
    }
}

#endif
