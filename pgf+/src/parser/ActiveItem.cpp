//
//  ActiveItem.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/parser/ActiveItem.h>

namespace gf {
    namespace parser {
        
        ActiveItem::ActiveItem(uint32_t begin, uint32_t category, gf::reader::CncFun* cncFun, const std::vector<uint32_t>& domain, uint32_t constituent, uint32_t position)
            : begin(begin), category(category), cncFun(cncFun), domain(domain), constituent(constituent), position(position) {
        }
        
        ActiveItem::~ActiveItem() {
            gf::release(cncFun);
        }
        
        uint32_t ActiveItem::getBegin() const {
            return begin;
        }
        
        uint32_t ActiveItem::getCategory() const {
            return category;
        }
        
        gf::reader::CncFun* ActiveItem::getFunction() const {
            return cncFun;
        }
        
        const std::vector<uint32_t>& ActiveItem::getDomain() const {
            return domain;
        }
        
        uint32_t ActiveItem::getConstituent() const {
            return constituent;
        }
        
        uint32_t ActiveItem::getPosition() const {
            return position;
        }
        
        gf::reader::Symbol* ActiveItem::nextSymbol() const {
            if (hasNextSymbol()) {
                return cncFun->getSequences().at(constituent)->getSymbols().at(position);
            }
            
            return NULL;
        }
        
        bool ActiveItem::hasNextSymbol() const {
            return position < cncFun->getSequences().at(constituent)->getSymbols().size();
        }
        
        bool ActiveItem::operator==(const ActiveItem& other) const {
            return begin == other.begin &&
                category == other.category &&
                cncFun == other.cncFun &&
                domain == other.domain &&
                constituent == other.constituent &&
                position == other.position;
        }
        
        bool ActiveItem::operator!=(const ActiveItem& other) const {
            return !(*this == other);
        }
        
        std::string ActiveItem::toString() const {
            std::string ret;
            
            ret = "[";
            ret+= gf::toString(begin) + ";";
            ret+= gf::toString(category) + "->" + cncFun->getName();
            ret+= "[" + domainToString() + "];";
            ret+= gf::toString(constituent) + ";";
            ret+= gf::toString(position);
            ret+= "]";
            
            return ret;
        }
        
        std::string ActiveItem::domainToString() const {
            std::string ret;
            
            for (std::vector<uint32_t>::const_iterator it = domain.begin(); it != domain.end(); it++) {
                ret+= (it == domain.begin() ? "" : ", ") + gf::toString(*it);
            }
            
            return ret;
        }
        
    }
}