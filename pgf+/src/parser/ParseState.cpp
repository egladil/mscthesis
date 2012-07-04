//
//  ParseState.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <assert.h>
#include <gf/parser/IMTree.h>
#include <gf/parser/ParseState.h>
#include <gf/reader/ArgConstSymbol.h>
#include <gf/reader/ToksSymbol.h>

namespace gf {
    namespace parser {
        
        ParseState::ParseState(gf::reader::Concrete* grammar, const std::string& startcat) throw (gf::UnknownCategoryException)
            : grammar(grammar), startcat(grammar->concreteCat(startcat)), chart(new Chart(100)), trie(new ParseTrie()), position(0) {
            this->startcat->addReference();
        }
        
        ParseState::~ParseState() {
            gf::release(grammar);
            gf::release(startcat);
            gf::release(chart);
            gf::release(trie);
        }
        
        
        void ParseState::compute() {
            active.push_back(new ActiveSet());
            
            while (!agenda.empty()) {
                processActiveItem(agenda.back());
                gf::release(agenda.back());
                agenda.pop_back();
            }
        }
        
        void ParseState::processActiveItem(ActiveItem* item) {
            if (!item->hasNextSymbol()) {
                if (chart->hasCategory(item->getCategory(), item->getConstituent(), item->getBegin(), position)) {
                    uint32_t cat;
                    std::vector<ActiveSet::ActiveItemIntInt> oldActive;
                    
                    cat = chart->getCategory(item->getCategory(), item->getConstituent(), item->getBegin(), position);
                    oldActive = active.at(position)->get(cat);
                    
                    for (std::vector<ActiveSet::ActiveItemIntInt>::iterator it = oldActive.begin(); it != oldActive.end(); it++) {
                        uint32_t r = it->_3;
                        gf::reader::CncFun* fun;
                        
                        fun = item->getFunction();
                        fun->addReference();
                        
                        agenda.push_back(new ActiveItem(position, cat, fun, item->getDomain(), r, 0));
                    }
                    
                    chart->addProduction(cat, item->getFunction(), item->getDomain());
                } else {
                    uint32_t cat;
                    std::vector<ActiveSet::ActiveItemInt> oldActive;
                    
                    cat = chart->generateFreshCategory(item->getCategory(), item->getConstituent(), item->getBegin(), position);
                    oldActive = active.at(item->getBegin())->get(item->getCategory(), item->getConstituent());
                    
                    for (std::vector<ActiveSet::ActiveItemInt>::iterator it = oldActive.begin(); it != oldActive.end(); it++) {
                        ActiveItem* ip = it->_1;
                        uint32_t d = it->_2;
                        std::vector<uint32_t> domain;
                        gf::reader::CncFun* fun;
                        
                        domain = ip->getDomain();
                        domain.at(d) = cat;
                        
                        fun = ip->getFunction();
                        fun->addReference();
                        
                        agenda.push_back(new ActiveItem(ip->getBegin(), ip->getCategory(), fun, domain, ip->getConstituent(), ip->getPosition() + 1));
                    }
                    
                    chart->addProduction(cat, item->getFunction(), item->getDomain());
                }
            } else {
                gf::reader::Symbol* next;
                gf::reader::ArgConstSymbol* arg;
                gf::reader::ToksSymbol* tok;
                
                next = item->nextSymbol();
                arg = dynamic_cast<gf::reader::ArgConstSymbol*>(next);
                tok = dynamic_cast<gf::reader::ToksSymbol*>(next);
                if (tok != NULL) {
                    gf::reader::CncFun* fun;
                    ActiveItem* ai;
                    std::vector<ActiveItem*>* stack;
                    
                    fun = item->getFunction();
                    fun->addReference();
                    
                    ai = new ActiveItem(item->getBegin(), item->getCategory(), fun, item->getDomain(), item->getConstituent(), item->getPosition() + 1);
                    
                    stack = trie->lookup(tok->getTokens());
                    if (stack == NULL) {
                        std::vector<ActiveItem*> newStack;
                        
                        newStack.push_back(ai);
                        trie->add(tok->getTokens(), newStack);
                    } else {
                        stack->push_back(ai);
                    }
                } else if (arg != NULL) {
                    uint32_t cat;
                    
                    cat = item->getDomain().at(arg->getArg());
                    
                    assert(position < active.size());
                    if (active.at(position)->add(cat, arg->getCons(), item, arg->getArg())) {
                        std::vector<gf::reader::ApplProduction*> prods;
                        
                        prods = chart->getProductions(cat);
                        for (std::vector<gf::reader::ApplProduction*>::iterator it = prods.begin(); it != prods.end(); it++) {
                            gf::reader::CncFun* fun;
                            
                            fun = (*it)->getFunction();
                            fun->addReference();
                            
                            agenda.push_back(new ActiveItem(position, cat, fun, (*it)->getDomain(), arg->getCons(), 0));
                        }
                        
                        for (std::vector<gf::reader::ApplProduction*>::iterator it = prods.begin(); it != prods.end(); it++) {
                            gf::release(*it);
                        }
                    }
                    
                    if (chart->hasCategory(cat, arg->getCons(), position, position)) {
                        uint32_t catN;
                        std::vector<uint32_t> domain;
                        gf::reader::CncFun* fun;

                        catN = chart->getCategory(cat, arg->getCons(), position, position);
                        
                        domain = item->getDomain();
                        domain.at(arg->getArg()) = catN;
                        
                        fun = item->getFunction();
                        fun->addReference();
                        
                        agenda.push_back(new ActiveItem(item->getBegin(), item->getCategory(), fun, domain, item->getConstituent(), item->getPosition() + 1));
                    }
                } else {
                    assert(0);
                }
            }
        }
        
        std::set<std::string> ParseState::predict() const {
            return trie->predict();
        }
        
        std::vector<gf::Tree*> ParseState::getTrees() const {
            std::vector<gf::Tree*> ret;
            std::vector<IMTree*> tmp;
            
            tmp = IMTree::buildTrees(chart, startcat, position);
            
            for (std::vector<IMTree*>::iterator it = tmp.begin(); it != tmp.end(); it++) {
                ret.push_back((*it)->toAbstract());
                gf::release(*it);
            }
            
            return ret;
        }
        
        bool ParseState::scan(const std::string& token) {
            std::vector<std::string> tokens;
            ParseTrie* newTrie;
            std::vector<ActiveItem*>* newAgenda;
            
            tokens.push_back(token);
            newTrie = trie->getSubTrie(tokens);
            if (newTrie == NULL) {
                return false;
            }
            
            newAgenda = newTrie->lookup(std::vector<std::string>());
            if (newAgenda == NULL) {
                return false;
            }
            
            newTrie->addReference();
            for (std::vector<ActiveItem*>::iterator it = newAgenda->begin(); it != newAgenda->end(); it++) {
                (*it)->addReference();
            }
            
            gf::release(trie);
            trie = newTrie;
            
            for (std::vector<ActiveItem*>::iterator it = agenda.begin(); it != agenda.end(); it++) {
                gf::release(*it);
            }
            agenda = *newAgenda;
            
            position++;
            
            compute();

            return true;
        }
        
        std::string ParseState::toString() const {
            std::string ret;
            
            ret = "= ParseState =\n";
            ret+= "== Chart ==\n";
            ret+= chart->toString();
            ret+= "== Trie ==\n";
            ret+= trie->toString();
            
            return ret;
        }
        
    }
}