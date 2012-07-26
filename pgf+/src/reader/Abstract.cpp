//
//  Abstract.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <assert.h>
#include <gf/reader/Abstract.h>
#include <gf/reader/StringLit.h>

namespace gf {
    namespace reader {
        
        static std::string defaultStartCategory = "Sentence";
        
        
        Abstract::Abstract(const std::string& name, const std::map<std::string, RLiteral*>& flags, const std::vector<AbsFun*>& absFuns, const std::vector<AbsCat*>& absCats)
            : name(name), flags(flags), absFuns(absFuns), absCats(absCats) {
            for (std::vector<AbsCat*>::const_iterator it = absCats.begin(); it != absCats.end(); it++) {
                categories.insert(std::make_pair((*it)->getName(), *it));
            }
                
            for (std::vector<AbsFun*>::const_iterator it = absFuns.begin(); it != absFuns.end(); it++) {
                functions.insert(std::make_pair((*it)->getName(), *it));
            }
        }
        
        Abstract::~Abstract() {
            for (std::map<std::string, RLiteral*>::iterator it = flags.begin(); it != flags.end(); it++) {
                gf::release(it->second);
            }
            
            for (std::vector<AbsFun*>::iterator it = absFuns.begin(); it != absFuns.end(); it++) {
                gf::release(*it);
            }
                 
            for (std::vector<AbsCat*>::iterator it = absCats.begin(); it != absCats.end(); it++) {
                gf::release(*it);
            }
        }
        
        const std::string& Abstract::getName() const {
            return name;
        }
        
        const std::string& Abstract::getStartCategory() const {
            std::map<std::string, RLiteral*>::const_iterator flag = flags.find("startcat");
            StringLit* strlit;
            
            if (flag == flags.end()) {
                return defaultStartCategory;
            }
            
            strlit = dynamic_cast<StringLit*>(flag->second);
            assert(strlit != NULL);
            
            return strlit->getValue();
        }
        
        std::vector<AbsFun*> Abstract::getFunctions(const std::string& returnType) const {
            std::vector<AbsFun*> ret;
            std::map<std::string, AbsCat*>::const_iterator cat;
            
            cat = categories.find(returnType);
            if (cat == categories.end()) {
                return ret;
            }
            
            for (std::vector<WeightedIdent*>::const_iterator it = cat->second->getFunctions().begin(); it != cat->second->getFunctions().end(); it++) {
                std::map<std::string, AbsFun*>::const_iterator fun;
                
                fun = functions.find((*it)->getIdent());
                if (fun != functions.end()) {
                    ret.push_back(fun->second);
                }
            }
            
            return ret;
        }
         
         const std::vector<AbsFun*>& Abstract::getAbsFuns() const {
             return absFuns;
         }
         
         const std::vector<AbsCat*>& Abstract::getAbsCats() const {
             return absCats;
         }
         
        
         std::string Abstract::toString() const {
             std::string ret;
             
             ret = "Name: " + name + ", flags: (";
             // TODO: concat of flags commented out in java??
             ret+= "), abstract functions: (";
             for (std::vector<AbsFun*>::const_iterator it = absFuns.begin(); it != absFuns.end(); it++) {
                 ret+= (*it)->toString();
             }
             ret+= "), concrete categories: (";
             for (std::vector<AbsCat*>::const_iterator it = absCats.begin(); it != absCats.end(); it++) {
                 ret+= (*it)->toString();
             }
             ret+= ")";
             
             return ret;
         }
        
    }
}