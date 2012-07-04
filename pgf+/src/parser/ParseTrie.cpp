//
//  ParseTrie.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/parser/ParseTrie.h>

namespace gf {
    namespace parser {
        
        ParseTrie::ParseTrie(const std::vector<ActiveItem*>& value)
            : value(value) {
        }
        
        ParseTrie::ParseTrie() {
        }
        
        ParseTrie::~ParseTrie() {
            for (std::vector<ActiveItem*>::iterator it = value.begin(); it != value.end(); it++) {
                gf::release(*it);
            }
            for (std::map<std::string, ParseTrie*>::iterator it = child.begin(); it != child.end(); it++) {
                gf::release(it->second);
            }
        }
        
        bool ParseTrie::add(const std::vector<std::string>& key, const std::vector<ActiveItem*>& value) {
            std::map<std::string, ParseTrie*>::const_iterator sub;
            std::vector<std::string> subkey;
            
            if (key.empty()) {
                for (std::vector<ActiveItem*>::iterator it = this->value.begin(); it != this->value.end(); it++) {
                    gf::release(*it);
                }
                this->value = value;
                return true;
            }
            
            sub = child.find(key.front());
            if (sub == child.end()) {
                sub = child.insert(std::make_pair(key.front(), new ParseTrie())).first;
            }
            
            subkey.insert(subkey.end(), key.begin() + 1, key.end());
            
            return sub->second->add(subkey, value);
        }
        
        std::vector<ActiveItem*>* ParseTrie::lookup(const std::vector<std::string>& key) {
            ParseTrie* tree;
            
            tree = getSubTrie(key);
            if (tree == NULL) {
                return NULL;
            }
            
            return &tree->value;
        }
        
        const std::vector<ActiveItem*>* ParseTrie::lookup(const std::vector<std::string>& key) const {
            const ParseTrie* tree;
            
            tree = getSubTrie(key);
            if (tree == NULL) {
                return NULL;
            }
            
            return &tree->value;
        }
        
        ParseTrie* ParseTrie::getSubTrie(const std::vector<std::string>& key) {
            std::map<std::string, ParseTrie*>::const_iterator sub;
            std::vector<std::string> subkey;
            
            if (key.empty()) {
                return this;
            }
            
            sub = child.find(key.front());
            if (sub == child.end()) {
                return NULL;
            }
            
            subkey.insert(subkey.end(), key.begin() + 1, key.end());
            
            return sub->second->getSubTrie(subkey);
        }
        
        const ParseTrie* ParseTrie::getSubTrie(const std::vector<std::string>& key) const {
            std::map<std::string, ParseTrie*>::const_iterator sub;
            std::vector<std::string> subkey;
            
            if (key.empty()) {
                return this;
            }
            
            sub = child.find(key.front());
            if (sub == child.end()) {
                return NULL;
            }
            
            subkey.insert(subkey.end(), key.begin() + 1, key.end());
            
            return const_cast<const ParseTrie*>(sub->second)->getSubTrie(subkey);
        }
        
        std::set<std::string> ParseTrie::predict() const {
            std::set<std::string> ret;
            
            for (std::map<std::string, ParseTrie*>::const_iterator it = child.begin(); it != child.end(); it++) {
                ret.insert(it->first);
            }
            
            return ret;
        }
        
        std::string ParseTrie::toString() const {
            return toStringWithPrefix("");
        }
        
        std::string ParseTrie::toStringWithPrefix(const std::string& prefix) const {
            std::string ret;
            
            ret = prefix + "<";
            for (std::vector<ActiveItem*>::const_iterator it = value.begin(); it != value.end(); it++) {
                ret+= (it == value.begin() ? "" : ", ") + (*it)->toString();
            }
            ret+= ">\n";
            for (std::map<std::string, ParseTrie*>::const_iterator it = child.begin(); it != child.end(); it++) {
                ret+= prefix + it->first + ":\n";
                ret+= it->second->toStringWithPrefix(prefix) + "\n";
            }
            
            return ret;
        }
        
    }
}