//
//  Generator.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <stdlib.h>
#include <gf/Generator.h>
#include <gf/reader/AbsCat.h>
#include <gf/reader/AbsFun.h>
#include <gf/reader/Hypo.h>
#include <gf/reader/WeightedIdent.h>

namespace gf {
    
    Generator::Generator(PGF* pgf)
        : pgf(pgf) {
        
        for (std::vector<gf::reader::AbsCat*>::const_iterator it = pgf->getAbstract()->getAbsCats().begin(); it != pgf->getAbstract()->getAbsCats().end(); it++) {
            gf::reader::AbsCat* abscat = *it;
            std::set<std::string> directFunctions;
            std::set<std::string> indirectFunctions;
            
            for (std::vector<gf::reader::WeightedIdent*>::const_iterator it2 = abscat->getFunctions().begin(); it2 != abscat->getFunctions().end(); it2++) {
                gf::reader::WeightedIdent* function = *it2;
                
                for (std::vector<gf::reader::AbsFun*>::const_iterator it3 = pgf->getAbstract()->getAbsFuns().begin(); it3 != pgf->getAbstract()->getAbsFuns().end(); it3++) {
                    gf::reader::AbsFun* absfun = *it3;
                    
                    if (function->getIdent() == absfun->getName()) {
                        if (absfun->getType()->getHypos().empty()) {
                            directFunctions.insert(function->getIdent());
                        } else {
                            indirectFunctions.insert(function->getIdent());
                        }
                        
                        break;
                    }
                }
            }
            
            directRules.insert(std::make_pair(abscat->getName(), directFunctions));
            indirectRules.insert(std::make_pair(abscat->getName(), indirectFunctions));
        }
    }
    
    Generator::~Generator() {
        gf::release(pgf);
    }
    
    Tree* Generator::generate() const throw(GeneratorException) {
        return generate(pgf->getAbstract()->startcat());
    }
    
    Tree* Generator::getDirect(const std::set<std::string>& dirFuns) const {
        uint32_t pos;
        std::set<std::string>::const_iterator it;
        
        pos = rand() % dirFuns.size();
        it = dirFuns.begin();
        for (uint32_t i = 0; i < pos; i++) {
            it++;
        }

        return new Function(*it);
    }
    
    Tree* Generator::getIndirect(const std::string& type, const std::set<std::string>& indirFuns) const throw(GeneratorException) {
        uint32_t pos;
        std::set<std::string>::const_iterator it;
        std::string functionName;
        
        pos = rand() % indirFuns.size();
        it = indirFuns.begin();
        for (uint32_t i = 0; i < pos; i++) {
            it++;
        }
        
        functionName = *it;
        
        for (std::vector<gf::reader::AbsFun*>::const_iterator it = pgf->getAbstract()->getAbsFuns().begin(); it != pgf->getAbstract()->getAbsFuns().end(); it++) {
            gf::reader::AbsFun* absfun = *it;
            std::vector<Tree*> exps;
            Tree* ret;
            
            if (absfun->getName() != functionName) {
                continue;
            }
            
            for (std::vector<gf::reader::Hypo*>::const_iterator it2 = absfun->getType()->getHypos().begin(); it2 != absfun->getType()->getHypos().end(); it2++) {
                gf::reader::Hypo* hypo = *it2;
                Tree* tree;
                
                tree = generate(hypo->getType()->getName());
                if (tree == NULL) {
                    for (std::vector<Tree*>::iterator it3 = exps.begin(); it3 != exps.end(); it3++) {
                        delete *it3;
                    }
                    
                    return NULL;
                }
                
                exps.push_back(tree);
            }
            
            ret = new Function(functionName);
            for (std::vector<Tree*>::iterator it2 = exps.begin(); it2 != exps.end(); it2++) {
                ret = new Application(ret, *it2);
            }
            
            return ret;
        }
        
        return NULL;
    }
    
    Tree* Generator::generate(const std::string& type) const throw(GeneratorException) {
        std::map<std::string, std::set<std::string> >::const_iterator directFunctions;
        std::map<std::string, std::set<std::string> >::const_iterator indirectFunctions;
        bool noDirect;
        bool noIndirect;
        
        if (type == "Integer") {
            return new Literal(new IntLiteral(generateInt()));
        } else if (type == "Float") {
            return new Literal(new FloatLiteral(generateDouble()));
        } else if (type == "String") {
            return new Literal(new StringLiteral(generateString()));
        }
        
        directFunctions = directRules.find(type);
        indirectFunctions = indirectRules.find(type);
        
        noDirect = directFunctions == directRules.end() || directFunctions->second.empty();
        noIndirect = indirectFunctions == indirectRules.end() || indirectFunctions->second.empty();
        
        if (noDirect && noIndirect) {
            throw GeneratorException("Cannot generate any expressions of type " + type);
        } else if (noDirect) {
            return getIndirect(type, indirectFunctions->second);
        } else if (noIndirect) {
            return getDirect(directFunctions->second);
        } else if (rand() % 5 < 2) {
            return getDirect(directFunctions->second);
        } else {
            return getIndirect(type, indirectFunctions->second);
        }
    }
    
    std::vector<Tree*> Generator::generateMany(const std::string& type, uint32_t count) const throw(GeneratorException) {
        std::map<std::string, std::set<std::string> >::const_iterator directFunctions;
        std::map<std::string, std::set<std::string> >::const_iterator indirectFunctions;
        std::vector<Tree*> ret;
        
        if (count == 0) {
            return std::vector<Tree*>();
        }
        
        directFunctions = directRules.find(type);
        indirectFunctions = indirectRules.find(type);
        
        if (directFunctions != directRules.end()) {
            for (std::set<std::string>::const_iterator it = directFunctions->second.begin(); it != directFunctions->second.end(); it++) {
                Tree* tree;
                
                tree = getDirect(directFunctions->second);
                if (tree == NULL) {
                    continue;
                }
                
                ret.push_back(tree);
                
                count--;
                if (count == 0) {
                    return ret;
                }
            }
        }
        
        if (indirectFunctions != indirectRules.end()) {
            for (std::set<std::string>::const_iterator it = indirectFunctions->second.begin(); it != indirectFunctions->second.end(); it++) {
                Tree* tree;
                
                tree = getIndirect(type, directFunctions->second);
                if (tree == NULL) {
                    continue;
                }
                
                ret.push_back(tree);
                
                count--;
                if (count == 0) {
                    return ret;
                }
            }
        }
        
        return ret;
    }
    
    std::string Generator::generateString() const {
        switch (rand() % 4) {
            case 0:
                return "x";
            case 1:
                return "y";
            case 2:
                return "foo";
            default:
                return "bar";
        }
    }
    
    uint32_t Generator::generateInt() const {
        return rand() % 100000;
    }
    
    double Generator::generateDouble() const {
        return (double) rand() / RAND_MAX;
    }
}

