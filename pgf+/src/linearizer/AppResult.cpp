//
//  AppResult.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-29.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/linearizer/AppResult.h>

namespace gf {
    namespace linearizer {
        
        AppResult::AppResult(gf::reader::CncFun* cncFun, CncType* cncType, const std::vector<CncType*>& cncTypes)
            : cncFun(cncFun), cncType(cncType), cncTypes(cncTypes) {
        }
        
        AppResult::~AppResult() {
            gf::release(cncFun);
            gf::release(cncType);
            
            for (std::vector<CncType*>::iterator it = cncTypes.begin(); it != cncTypes.end(); it++) {
                gf::release(*it);
            }
        }
        
        gf::reader::CncFun* AppResult::getConcreteFunction() const {
            return  cncFun;
        }
        
        CncType* AppResult::getConcreteType() const {
            return cncType;
        }
        
        const std::vector<CncType*>& AppResult::getConcreteTypes() const {
            return cncTypes;
        }
        
    }
}