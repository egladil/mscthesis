//
//  IMTree.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _IMTree_h
#define _IMTree_h

#include <string>
#include <vector>
#include <gf/ParseException.h>
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
            
            virtual gf::Tree* toAbstract(const std::vector<std::string>& args) const = 0;
            
        public:
            virtual ~IMTree();
            
            virtual gf::Tree* toAbstract();
            
            static std::vector<IMTree*> buildTrees(Chart* chart, gf::reader::CncCat* cncCat, uint32_t length) throw (gf::ParseException);
            static std::vector<IMTree*> mkTreesForCat(uint32_t cat, Chart* chart);
            static std::vector<IMTree*> mkTreesForProduction(gf::reader::ApplProduction* production, Chart* chart);
            static std::vector<std::vector<IMTree*> > listMixer(const std::vector<std::vector<IMTree*> >& src);
        };
        
    }
}

#endif
