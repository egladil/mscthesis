//
//  Type.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/reader/Type.h>

namespace gf {
    namespace reader {
        
        Type::Type(const std::vector<Hypo*>& hypos, const std::string name, const std::vector<Expr*>& expressions)
            : hypos(hypos), name(name), expressions(expressions) {
        }
        
        Type::~Type() {
            for (std::vector<Hypo*>::iterator it = hypos.begin(); it != hypos.end(); it++) {
                gf::release(*it);
            }
            for (std::vector<Expr*>::iterator it = expressions.begin(); it != expressions.end(); it++) {
                gf::release(*it);
            }
        }
        
        std::string Type::toString() const {
            std::string ret;
            
            for (std::vector<Hypo*>::const_iterator it = hypos.begin(); it != hypos.end(); it++) {
                Hypo* hypo = *it;
                
                if (hypo->getType()->isFunctionType()) {
                    ret+= "(";
                }
                
                ret+= hypo->toString();
                
                if (hypo->getType()->isFunctionType()) {
                    ret+= ")";
                }
                
                ret+= " -> ";
            }
            
            ret+= name;

            for (std::vector<Expr*>::const_iterator it = expressions.begin(); it != expressions.end(); it++) {
                ret+= " " + (*it)->toString();
            }
            
            return ret;
        }
        
        const std::vector<Hypo*>& Type::getHypos() const {
            return hypos;
        }
        
        const std::string& Type::getName() const {
            return name;
        }
        
        const std::vector<Expr*>& Type::getExprs() const {
            return expressions;
        }
        
        bool Type::isFunctionType() const {
            return !hypos.empty();
        }
        bool Type::isFunctorType() const {
            for (std::vector<Hypo*>::const_iterator it = hypos.begin(); it != hypos.end(); it++) {
                if ((*it)->getType()->isFunctionType()) {
                    return true;
                }
            }
            
            return false;
        }
        
    }
}