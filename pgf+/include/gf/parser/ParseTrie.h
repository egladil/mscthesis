//
//  ParseTrie.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _ParseTrie_h
#define _ParseTrie_h

#include <map>
#include <set>
#include <vector>
#include <gf/RefBase.h>
#include <gf/parser/ActiveItem.h>

namespace gf {
    namespace parser {
        /**
         * The ParseTries are used to keep track of the possible next symbols.
         * It is a trie where the symbol (edge labels) are string (words) and the values (node) are agendas
         * (stacks of ActiveItems)
         * The parse tries is used in the parsing algorithm when a dot is before a token. Then the dot is
         * moved after the tokens and the resulting active item is added to the trie (to the agenda indexed by
         * the words of the token.)
         * Then the scan operation is a simple lookup in the trie...
         * The trie is also used for predictions.
         * In gf, a token in a rule can consist of multiple words (separated by a whitespace), thus the trie is
         * needed and cannot be replaced by a simple map.
         **/
        class ParseTrie : public RefBase {
        private:
            std::vector<ActiveItem*> value;
            std::map<std::string, ParseTrie*> child;
            
        public:
            /**
             * @param value the value at this node.
             */
            ParseTrie(const std::vector<ActiveItem*>& value);
            
            ParseTrie();
            virtual ~ParseTrie();
            
            virtual bool add(const std::vector<std::string>& key, const std::vector<ActiveItem*>& value);
            
            virtual std::vector<ActiveItem*>* lookup(const std::vector<std::string>& key);
            virtual const std::vector<ActiveItem*>* lookup(const std::vector<std::string>& key) const;
            
            virtual ParseTrie* getSubTrie(const std::vector<std::string>& key);
            virtual const ParseTrie* getSubTrie(const std::vector<std::string>& key) const;
            
            virtual std::set<std::string> predict() const;
            
            virtual std::string toString() const;
            virtual std::string toStringWithPrefix(const std::string& prefix) const;
        };
        
    }
}


#endif
