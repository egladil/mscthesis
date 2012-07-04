//
//  Chart.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _Chart_h
#define _Chart_h

#include <stdint.h>
#include <map>
#include <set>
#include <vector>
#include <gf/RefBase.h>
#include <gf/reader/ApplProduction.h>
#include <gf/reader/CncFun.h>
#include <gf/reader/CoerceProduction.h>
#include <gf/reader/Production.h>

namespace gf {
    namespace parser {
        
        class Chart : public RefBase {
        private:
            uint32_t nextCategory;
            std::map<uint32_t, std::set<gf::reader::Production*> > productionSets;
            std::map<std::vector<uint32_t>, uint32_t> categoryBookKeeper;
            
            
            std::vector<gf::reader::ApplProduction*> uncoerce(gf::reader::Production* production) const;
            
        public:
            Chart(uint32_t nextCategory);
            virtual ~Chart();
            
            virtual bool addProduction(gf::reader::Production* production);
            virtual bool addProduction(uint32_t category, gf::reader::CncFun* function, const std::vector<uint32_t>& domain);
            
            virtual std::vector<gf::reader::ApplProduction*> getProductions(uint32_t resultCategory) const;
            
            virtual uint32_t getFreshCategory(uint32_t oldCat, uint32_t cons, uint32_t begin, uint32_t end);
            
            virtual bool hasCategory(uint32_t oldCat, uint32_t cons, uint32_t begin, uint32_t end) const;
            virtual uint32_t getCategory(uint32_t oldCat, uint32_t cons, uint32_t begin, uint32_t end) const;

            virtual uint32_t generateFreshCategory(uint32_t oldCat, uint32_t cons, uint32_t begin, uint32_t end);
            
            virtual std::string toString() const;
        };
        
    }
}


#endif
