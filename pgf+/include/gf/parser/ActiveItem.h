//
//  ActiveItem.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _ActiveItem_h
#define _ActiveItem_h

#include <stdint.h>
#include <vector>
#include <gf/RefBase.h>
#include <gf/reader/CncFun.h>
#include <gf/reader/Symbol.h>

namespace gf {
    namespace parser {
        
        class ActiveItem : public RefBase {
        private:
            uint32_t begin;
            uint32_t category;
            gf::reader::CncFun* cncFun;
            std::vector<uint32_t> domain;
            uint32_t constituent;
            uint32_t position;
            
        public:
            ActiveItem(uint32_t begin, uint32_t category, gf::reader::CncFun* cncFun, const std::vector<uint32_t>& domain, uint32_t constituent, uint32_t position);
            virtual ~ActiveItem();
            
            virtual gf::reader::Symbol* nextSymbol() const;

            virtual bool hasNextSymbol() const;
            
            virtual bool operator==(const ActiveItem& other) const;
            virtual bool operator!=(const ActiveItem& other) const;
            
            virtual std::string toString() const;
            virtual std::string domainToString() const;
        };
        
    }
}

#endif
