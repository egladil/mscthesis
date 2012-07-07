//
//  ActiveSet.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-05.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/parser/ActiveSet.h>

namespace gf {
    namespace parser {
        
        ActiveSet::ActiveSet() {
        }
        
        ActiveSet::~ActiveSet() {
            for (std::map<uint32_t, std::multimap<uint32_t, ActiveItemInt> >::iterator it = store.begin(); it != store.end(); it++) {
                for (std::multimap<uint32_t, ActiveItemInt>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                    gf::release(it2->second._1);
                }
            }
        }
        
        bool ActiveSet::add(uint32_t cat, uint32_t cons, ActiveItem* item, uint32_t cons2) {
            std::map<uint32_t, std::multimap<uint32_t, ActiveItemInt> >::iterator multi;
            ActiveItemInt val = {item, cons2};
            
            multi = store.find(cat);
            if (multi == store.end()) {
                multi = store.insert(std::make_pair(cat, std::multimap<uint32_t, ActiveItemInt>())).first;
            } else {
                std::pair<std::multimap<uint32_t, ActiveItemInt>::const_iterator, std::multimap<uint32_t, ActiveItemInt>::const_iterator> range;
                
                range = multi->second.equal_range(cons);
                for (std::multimap<uint32_t, ActiveItemInt>::const_iterator it = range.first; it != range.second; it++) {
                    if (it->second._1 == item && it->second._2 == cons2) {
                        return false;
                    }
                }
            }
            
            multi->second.insert(std::make_pair(cons, val));
            return true;
        }
        
        std::vector<ActiveSet::ActiveItemIntInt> ActiveSet::get(uint32_t cat) const {
            std::map<uint32_t, std::multimap<uint32_t, ActiveItemInt> >::const_iterator multi;
            std::vector<ActiveItemIntInt> ret;
            
            multi = store.find(cat);
            if (multi == store.end()) {
                return ret;
            }
            
            for (std::multimap<uint32_t, ActiveItemInt>::const_iterator it = multi->second.begin(); it != multi->second.end(); it++) {
                ActiveItemIntInt val = {it->second._1, it->second._2, it->first};
                
                val._1->addReference();
                ret.push_back(val);
            }
            
            return ret;
        }
        
        std::vector<ActiveSet::ActiveItemInt> ActiveSet::get(uint32_t cat, uint32_t cons) const {
            std::map<uint32_t, std::multimap<uint32_t, ActiveItemInt> >::const_iterator multi;
            std::vector<ActiveItemInt> ret;
            std::pair<std::multimap<uint32_t, ActiveItemInt>::const_iterator, std::multimap<uint32_t, ActiveItemInt>::const_iterator> range;
            
            multi = store.find(cat);
            if (multi == store.end()) {
                return ret;
            }
            
            range = multi->second.equal_range(cons);
            for (std::multimap<uint32_t, ActiveItemInt>::const_iterator it = range.first; it != range.second; it++) {
                ActiveItemInt val = it->second;
                
                val._1->addReference();
                ret.push_back(val);
            }
            
            return ret;
        }
        
    }
}