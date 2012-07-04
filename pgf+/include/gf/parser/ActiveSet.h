//
//  ActiveSet.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _ActiveSet_h
#define _ActiveSet_h

#include <stdint.h>
#include <map>
#include <vector>
#include <gf/RefBase.h>
#include <gf/parser/ActiveItem.h>

namespace gf {
    namespace parser {
        
        class ActiveSet : public RefBase {
        public:
            struct ActiveItemInt {
                ActiveItem* _1;
                uint32_t _2;
            };
            
            struct ActiveItemIntInt {
                ActiveItem* _1;
                uint32_t _2;
                uint32_t _3;
            };
            
        private:
            std::map<uint32_t, std::multimap<uint32_t, ActiveItemInt> > store;
            
        public:
            ActiveSet();
            virtual ~ActiveSet();
            
            virtual bool add(uint32_t cat, uint32_t cons, ActiveItem* item, uint32_t cons2);

            virtual std::vector<ActiveItemIntInt> get(uint32_t cat) const;
            
            virtual std::vector<ActiveItemInt> get(uint32_t cat, uint32_t cons) const;
        };
        
    }
}

#endif
