//
//  Sequence.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/Sequence.h>

namespace gf {
    namespace reader {
        
        Sequence::Sequence(const std::vector<Symbol*>& symbols)
            : symbols(symbols) {
        }
        
        Sequence::~Sequence() {
            for (std::vector<Symbol*>::iterator it = symbols.begin(); it != symbols.end(); it++) {
                gf::release(*it);
            }
        }
        
        Symbol* Sequence::getSymbol(uint32_t index) const {
            // TODO: Range check
            return symbols.at(index);
        }
        
        size_t Sequence::length() const {
            return symbols.size();
        }
        
        const std::vector<Symbol*> Sequence::getSymbols() const {
            return symbols;
        }
        
        std::string Sequence::toString() const {
            std::string ret;
            
            ret = "Symbols: [";
            for (std::vector<Symbol*>::const_iterator it = symbols.begin(); it != symbols.end(); it++) {
                ret+= (it == symbols.begin() ? "" : " ") + (*it)->toString();
            }
            
            ret+= "]";
            
            return ret;
        }
        
    }
}