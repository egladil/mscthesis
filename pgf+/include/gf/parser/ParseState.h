//
//  ParseState.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _ParseState_h
#define _ParseState_h

#include <stdint.h>
#include <set>
#include <string>
#include <vector>
#include <gf/RefBase.h>
#include <gf/UnknownCategoryException.h>
#include <gf/parser/ActiveItem.h>
#include <gf/parser/ActiveSet.h>
#include <gf/parser/Chart.h>
#include <gf/parser/ParseTrie.h>
#include <gf/reader/CncCat.h>
#include <gf/reader/Concrete.h>
#include <gf/trees/Absyn.H>

namespace gf {
    namespace parser {
        
        class ParseState : public RefBase {
        private:
            /* final */ gf::reader::Concrete* grammar;
            /* final */ gf::reader::CncCat* startcat;
            /* final */ Chart* chart;
            ParseTrie* trie;
            std::vector<ActiveItem*> agenda;
            uint32_t position;
            
            /**
             * 'active' is the set of all the S_k's, holding the active items which are not
             * on the agenda.
             */
            std::vector<ActiveSet*> active;
            
            
            void compute();
            
            void processActiveItem(ActiveItem* item);
            
        public:
            ParseState(gf::reader::Concrete* grammar, const std::string& startcat) throw (gf::UnknownCategoryException);
            virtual ~ParseState();
            
            /**
             * returns the set of possible next words
             */
            virtual std::set<std::string> predict() const;
            
            virtual std::vector<Tree*> getTrees() const;
            
            virtual bool scan(const std::string& token);
            
            virtual std::string toString() const;
            
        };
        
    }
}

#endif
