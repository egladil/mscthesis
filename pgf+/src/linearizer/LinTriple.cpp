//
//  LinTriple.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-29.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/linearizer/LinTriple.h>

namespace gf {
    namespace linearizer {
        
        LinTriple::LinTriple(uint32_t fId, CncType* cncType, const std::vector<std::vector<BracketedToken*> >& linTable)
            : fId(fId), cncType(cncType), linTable(linTable) {
        }
        
        LinTriple::~LinTriple() {
            gf::release(cncType);
            for (std::vector<std::vector<BracketedToken*> >::iterator it = linTable.begin(); it != linTable.end(); it++) {
                for (std::vector<BracketedToken*>::iterator it2 = it->begin(); it2 != it->end(); it2++) {
                    gf::release(*it2);
                }
            }
        }
        
        uint32_t LinTriple::getFId() const {
            return fId;
        }
        
        CncType* LinTriple::getConcreteType() const {
            return cncType;
        }
        
        const std::vector<std::vector<BracketedToken*> >& LinTriple::getLinTable() const {
            return linTable;
        }
        
        std::string LinTriple::toString() const {
            std::string ret;
            
            ret = "id: ";
            ret+= gf::toString(fId);
            ret+= " cnctype: (";
            ret+= cncType->toString();
            ret+= ") bracketedToken: [";
            for (std::vector<std::vector<BracketedToken*> >::const_iterator it = linTable.begin(); it != linTable.end(); it++) {
                ret+= it == linTable.begin() ? "[" : ", [";
                for (std::vector<BracketedToken*>::const_iterator it2 = it->begin(); it2 != it->end(); it2++) {
                    ret+= (it2 == it->begin() ? "" : ", ") + (*it2)->toString();
                }
                ret+= "]";
            }
            ret+= "]";
            
            return ret;
        }
        
    }
}