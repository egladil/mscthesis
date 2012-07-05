//
//  IMTree.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-05.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/parser/IMApplication.h>
#include <gf/parser/IMTree.h>

namespace gf {
    namespace parser {
        
        IMTree::IMTree() {
        }
        
        IMTree::~IMTree() {
        }
        
        std::vector<IMTree*> IMTree::buildTrees(Chart* chart, gf::reader::CncCat* cncCat, uint32_t length) throw (gf::ParseException) {
            std::vector<IMTree*> ret;
            
            for (uint32_t catID = cncCat->getFirstId(); catID <= cncCat->getLastId(); catID++) {
                if (chart->hasCategory(catID, 0, 0, length)) {
                    std::vector<IMTree*> tmp;
                    uint32_t cat;
                    
                    cat = chart->getCategory(catID, 0, 0, length);
                    
                    tmp = mkTreesForCat(cat, chart);
                    ret.insert(ret.end(), tmp.begin(), tmp.end());
                }
            }
            
            return ret;
        }
        
        std::vector<IMTree*> IMTree::mkTreesForCat(uint32_t cat, Chart* chart) {
            std::vector<gf::reader::ApplProduction*> productions;
            std::vector<IMTree*> ret;
            
            productions = chart->getProductions(cat);
            for (std::vector<gf::reader::ApplProduction*>::iterator it = productions.begin(); it != productions.end(); it++) {
                std::vector<IMTree*> tmp;
                
                tmp = mkTreesForProduction(*it, chart);
                ret.insert(ret.end(), tmp.begin(), tmp.end());
            }
            
            
            return ret;
        }
        
        std::vector<IMTree*> IMTree::mkTreesForProduction(gf::reader::ApplProduction* production, Chart* chart) {
            std::vector<IMTree*> ret;
            std::vector<std::vector<IMTree*> > src;
            std::vector<std::vector<IMTree*> > mix;
            
            if (production->getDomain().empty()) {
                ret.push_back(new IMApplication(production->getFunction()->getName(), std::vector<IMTree*>()));
                return ret;
            }
            
            for (std::vector<uint32_t>::const_iterator it = production->getDomain().begin(); it != production->getDomain().end(); it++) {
                src.push_back(mkTreesForCat(*it, chart));
            }
            mix = listMixer(src);
            
            for (std::vector<std::vector<IMTree*> >::iterator args = mix.begin(); args != mix.end(); args++) {
                ret.push_back(new IMApplication(production->getFunction()->getName(), *args));
            }
            
            return ret;
        }
        
        std::vector<std::vector<IMTree*> > IMTree::listMixer(const std::vector<std::vector<IMTree*> >& src) {
            std::vector<std::vector<IMTree*> > ret;
            std::vector<std::vector<IMTree*> > tail;
            
            if (src.empty()) {
                return ret;
            } else if (src.size() == 1) {
                for (std::vector<IMTree*>::const_iterator it = src.front().begin(); it != src.front().end(); it++) {
                    std::vector<IMTree*> tmp;
                    
                    tmp.push_back(*it);
                    ret.push_back(tmp);
                }
                
                return ret;
            }
            
            tail.insert(tail.end(), src.begin() + 1, src.end());
            for (std::vector<IMTree*>::const_iterator first = src.front().begin(); first != src.front().end(); first++) {
                std::vector<std::vector<IMTree*> > mix;
                
                mix = listMixer(tail);
                for (std::vector<std::vector<IMTree*> >::iterator then = mix.begin(); then != mix.end(); then++) {
                    std::vector<IMTree*> tmp;
                    
                    tmp.push_back(*first);
                    tmp.insert(tmp.end(), then->begin(), then->end());
                    
                    ret.push_back(tmp);
                }
            }
            
            return ret;
        }
        
    }
}