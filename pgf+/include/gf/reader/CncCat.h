//
//  CncCat.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__CncCat_h
#define pgf__CncCat_h

#include <stdint.h>
#include <string>
#include <vector>

#include <gf/RefBase.h>

namespace gf {
    namespace reader {
        
        /**
         * Concrete categories are mapings from category names (abstract-categories)
         * to multiple, conjoint, concrete categories.
         * They are represented in the pgf binary by :
         *  - the name of the abstract category (ex: Adj)
         *  - the first concrete categoy (ex : C18)
         *  - the last corresponding concrete category (ex : C21)
         *  - a list of labels (names of fields in the pmcfg tuples)
         * Here we will keep only the indices.
         */
        class CncCat : public gf::RefBase {
        private:
            std::string name;
            uint32_t firstFId;
            uint32_t lastFId;
            
        public:
            CncCat(const std::string& name, uint32_t firstFId, uint32_t lastFId, const std::vector<std::string>& labels);
            virtual ~CncCat();
            
            virtual std::string toString() const;
            
            virtual const std::string& getName() const;
            virtual uint32_t getFirstId() const;
            virtual uint32_t getLastId() const;
        };
        
    }
}

#endif
