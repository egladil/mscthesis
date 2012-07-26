//
//  GenerateTrees.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-26.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/GenerateTrees.h>
#include <gf/reader/Type.h>

namespace gf {
    
    GenerateTrees::GenerateTrees(gf::reader::Abstract* abstract) 
        : abstract(abstract) {
    }
    
    GenerateTrees::GenerateTrees(gf::PGF* pgf)
        : abstract(pgf->getAbstract()) {
        abstract->addReference();
        gf::release(pgf);
    }
    
    GenerateTrees::~GenerateTrees() {
        gf::release(abstract);
    }
    
    std::vector<Tree*> GenerateTrees::generateTrees(const std::string& startcat, uint32_t depth) const {
        std::vector<gf::reader::AbsFun*> functions;
        std::vector<Tree*> ret;
        
        functions = abstract->getFunctions(startcat);
        for (std::vector<gf::reader::AbsFun*>::const_iterator it = functions.begin(); it != functions.end(); it++) {
            gf::reader::AbsFun* absfun = *it;
            
            if (depth > 0 || absfun->getType()->getHypos().empty()) {
                std::vector<Tree*> tmp;
                
                tmp = generateTrees(absfun, depth);
                ret.insert(ret.end(), tmp.begin(), tmp.end());
            }
        }
        
        return ret;
    }
    
    /**
     * Functions that makes every possible combination of items from
     * an array of collection while respecting the order of the collections.
     */
    static std::vector<std::vector<Tree*> > combine(const std::vector<std::vector<Tree*> >& source) {
        std::vector<std::vector<Tree*>::const_iterator > state;
        std::vector<Tree*> combination;
        std::vector<std::vector<Tree*> > ret;
        
        for (std::vector<std::vector<Tree*> >::const_iterator it = source.begin(); it != source.end(); it++) {
            if (it->empty()) {
                return std::vector<std::vector<Tree*> >();
            }
            
            combination.push_back(it->front());
            state.push_back(it->begin() + 1);
        }
        ret.push_back(combination);
        
        for (int pos = source.size() - 1; pos >= 0; ) {
            if (state[pos] != source[pos].end()) {
                combination[pos] = *state[pos];
                state[pos]++;
                if (pos < source.size() - 1) {
                    pos++;
                }
            } else {
                state[pos] = source[pos].begin();
                pos--;
            }
            
            ret.push_back(combination);
        }
        
        
        return ret;
    }
    
    std::vector<Tree*> GenerateTrees::generateTrees(gf::reader::AbsFun* absfun, uint32_t depth) const {
        std::vector<std::vector<Tree*> > children;
        std::vector<std::vector<Tree*> > combined;
        std::vector<Tree*> ret;
        
        if (absfun->getType()->isFunctorType()) {
            // Functors are not supported.
            return std::vector<Tree*>();
        }
        
        for (std::vector<gf::reader::Hypo*>::const_iterator it = absfun->getType()->getHypos().begin(); it != absfun->getType()->getHypos().end(); it++) {
            gf::reader::Hypo* hypo = *it;
            
            children.push_back(generateTrees(hypo->getType()->getName(), depth - 1));
        }
        
        combined = combine(children);
        for (std::vector<std::vector<Tree*> >::const_iterator it = combined.begin(); it != combined.end(); it++) {
            Tree* tree;
            
            tree = new Function(absfun->getName());
            for (std::vector<Tree*>::const_iterator it2 = it->begin(); it2 != it->end(); it2++) {
                tree = new Application(tree, *it2);
            }
            
            ret.push_back(tree);
        }
        
        return ret;
    }
    
}
