//
//  AppResult.h
//  
//
//  Created by Emil Djupfeldt on 2012-06-28.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _AppResult_h
#define _AppResult_h

#include <vector>

#include <gf/RefBase.h>
#include <gf/reader/CncFun.h>
#include <gf/linearizer/CncType.h>

namespace gf {
    namespace linearizer {
        
        class AppResult : public RefBase {
        private:
            gf::reader::CncFun* cncFun;
            CncType* cncType;
            std::vector<CncType*> cncTypes;
            
        public:
            AppResult(gf::reader::CncFun* cncFun, CncType* cncType, const std::vector<CncType*>& cncTypes);
            virtual ~AppResult();
            
            virtual gf::reader::CncFun* getConcreteFunction() const;
            virtual CncType* getConcreteType() const;
            virtual const std::vector<CncType*>& getConcreteTypes() const;
        };
        
    }
}

#endif
