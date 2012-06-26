//
//  AbsCat.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/AbsCat.h>

namespace gf {
    namespace reader {
        
        AbsCat::AbsCat(const std::string& name, const std::vector<Hypo*>& hypos, const std::vector<WeightedIdent*>& functions)
            : name(name), hypos(hypos), functions(functions) {
        }
        
        AbsCat::~AbsCat() {
            for (std::vector<Hypo*>::iterator it = hypos.begin(); it != hypos.end(); it++) {
                gf::release(*it);
            }
            
            for (std::vector<WeightedIdent*>::iterator it = functions.begin(); it != functions.end(); it++) {
                gf::release(*it);
            }
        }
        
        const std::string& AbsCat::getName() const {
            return name;
        }
        
        const std::vector<Hypo*>& AbsCat::getHypos() const {
            return hypos;
        }
        
        const std::vector<WeightedIdent*>& AbsCat::getFunctions() const {
            return functions;
        }
        
        std::string AbsCat::toString() const {
            std::string ret;
            
            ret = "Name: " + name + ", Hypotheses: (";
            
            for (std::vector<Hypo*>::const_iterator it = hypos.begin(); it != hypos.end(); it++) {
                ret+= (it == hypos.begin() ? "" : " ") + (*it)->toString();
            }
            
            ret+= ")";
            
            return ret;
        }
        
    }
}