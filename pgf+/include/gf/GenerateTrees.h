//
//  GenerateTrees.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-26.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _GenerateTrees_h
#define _GenerateTrees_h

#include <stdint.h>
#include <string>
#include <vector>
#include <gf/PGF.h>
#include <gf/RefBase.h>
#include <gf/reader/AbsFun.h>
#include <gf/reader/Abstract.h>
#include <gf/trees/Absyn.H>

namespace gf {
    
    class GenerateTrees : public RefBase {
    private:
        gf::reader::Abstract* abstract;
        
        std::vector<Tree*> generateTrees(gf::reader::AbsFun* absfun, uint32_t depth) const;
        
    public:
        GenerateTrees(gf::reader::Abstract* abstract);
        GenerateTrees(gf::PGF* pgf);
        virtual ~GenerateTrees();
        
        /**
         * Generates all {@link Tree}s where the root of the tree is the 
         * given category and the depth is at most 'depth'
         * @param startcat  Root category of the tree
         * @param depth     Maximum depth of the tree
         * @return          A collection of trees
         **/
        virtual std::vector<Tree*> generateTrees(const std::string& startcat, uint32_t depth) const;
        
    };
    
}

#endif
