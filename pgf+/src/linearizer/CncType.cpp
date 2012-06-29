//
//  CncType.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-29.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/linearizer/CncType.h>

namespace gf {
    namespace linearizer {
        
        CncType::CncType(const std::string& cId, uint32_t fId)
            : cId(cId), fId(fId) {
        }
        
        CncType::~CncType() {
        }
        
        const std::string& CncType::getCId() const {
            return cId;
        }
        
        uint32_t CncType::getFId() const {
            return fId;
        }
        
        std::string CncType::toString() const {
            std::string ret;
            
            ret = "name: ";
            ret+= cId;
            ret+= ", fid: ";
            ret+= gf::toString(fId);
            
            return ret;
        }
        
    }
}