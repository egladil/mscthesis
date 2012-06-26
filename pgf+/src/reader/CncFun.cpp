//
//  CncFun.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/CncFun.h>

namespace gf {
    namespace reader {
        
        CncFun::CncFun(const std::string& name, const std::vector<Sequence*>& sequences)
        : name(name), sequences(sequences) {
        }
        
        CncFun::~CncFun() {
            for (std::vector<Sequence*>::iterator it = sequences.begin(); it != sequences.end(); it++) {
                gf::release(*it);
            }
        }
        
        const std::string& CncFun::getName() const {
            return name;
        }
        
        const std::vector<Sequence*>& CncFun::getSequences() const {
            return sequences;
        }
        
        Sequence* CncFun::sequence(uint32_t index) const {
            // TODO: Bounds checking
            return sequences.at(index);
        }
        
        const Symbol* CncFun::symbol(uint32_t seqIndex, uint32_t symbIndex) const {
            // TODO: Bounds checking.
            return sequence(seqIndex)->getSymbols().at(symbIndex);
        }
        
        size_t CncFun::size() const {
            return sequences.size();
        }
        
        std::string CncFun::toString() const {
            std::string ret;
            
            ret = "Name: ";
            ret+= name;
            ret+= ", indices:";
            for (std::vector<Sequence*>::const_iterator it = sequences.begin(); it != sequences.end(); it++) {
                ret+= " " + (*it)->toString();
            }
            
            return ret;
        }
        
    }
}