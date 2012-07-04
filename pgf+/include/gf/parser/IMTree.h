//
//  IMTree.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _IMTree_h
#define _IMTree_h

#include <vector>
#include <gf/RefBase.h>
#include <gf/parser/Chart.h>
#include <gf/reader/ApplProduction.h>
#include <gf/reader/CncCat.h>
#include <gf/trees/Absyn.h>

namespace gf {
    namespace parser {
        
        class IMTree : public RefBase {
        private:
            
        protected:
            IMTree();
            
        public:
            virtual ~IMTree();
            
            virtual gf::Tree* toAbstract() const = 0;
            
            static std::vector<IMTree*> buildTrees(Chart* chart, gf::reader::CncCat* cncCat, uint32_t length);
            static std::vector<IMTree*> mkTreesForCat(uint32_t cat, Chart* chart);
            static std::vector<IMTree*> mkTreesForProduction(gf::reader::ApplProduction* production, Chart* chart);
            static std::vector<std::vector<IMTree*> > listMixer(const std::vector<std::vector<IMTree*> >& src);
        };
        
    }
}

#endif
