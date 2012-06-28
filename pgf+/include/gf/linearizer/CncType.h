//
//  CncType.h
//  
//
//  Created by Emil Djupfeldt on 2012-06-28.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _CncType_h
#define _CncType_h

#include <stdint.h>
#include <string>

#include <gf/RefBase.h>

namespace gf {
    namespace linearizer {
        
        class CncType : public RefBase {
        private:
            std::string cId;
            uint32_t fId;
            
        public:
            CncType(const std::string& cId, uint32_t fId);
            virtual ~CncType();
            
            virtual const std::string& getCId() const;
            virtual uint32_t getFId() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
