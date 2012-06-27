//
//  PGF.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-27.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/stringutil.h>
#include <gf/PGF.h>

namespace gf {
    
    PGF::PGF(uint32_t majorVersion, uint32_t minorVersion, const std::map<std::string, gf::reader::RLiteral*>& flags, gf::reader::Abstract* abstract, const std::vector<gf::reader::Concrete*>& concretes)
        : majorVersion(majorVersion), minorVersion(minorVersion), flags(flags), abstract(abstract) {
        for (std::vector<gf::reader::Concrete*>::const_iterator it = concretes.begin(); it != concretes.end(); it++) {
            gf::reader::Concrete* cnc = *it;
            this->concretes.insert(std::make_pair(cnc->getName(), cnc));
        }
    }
    
    PGF::~PGF() {
        for (std::map<std::string, gf::reader::RLiteral*>::iterator it = flags.begin(); it != flags.end(); it++) {
            gf::release(it->second);
        }
        
        gf::release(abstract);
        
        for (std::map<std::string, gf::reader::Concrete*>::iterator it = concretes.begin(); it != concretes.end(); it++) {
            gf::release(it->second);
        }
    }
    
    /* TODO: Cache set? */
    std::set<std::string> PGF::getConcreteNames() const {
        std::set<std::string> ret;
        
        for (std::map<std::string, gf::reader::Concrete*>::const_iterator it = concretes.begin(); it != concretes.end(); it++) {
            ret.insert(it->first);
        }
        
        return ret;
    }
    
    gf::reader::Concrete* PGF::getConcrete(const std::string& name) const {
        std::map<std::string, gf::reader::Concrete*>::const_iterator it = concretes.find(name);
        if (it == concretes.end()) {
            return NULL;
        }
        
        return it->second;
    }
    
    uint32_t PGF::getMajorVersion() const {
        return majorVersion;
    }
    
    uint32_t PGF::getMinorVersion() const {
        return minorVersion;
    }
    
    gf::reader::Abstract* PGF::getAbstract() const {
        return abstract;
    }
    
    bool PGF::hasConcrete(const std::string& name) const {
        return getConcrete(name) != NULL;
    }
    
    std::string PGF::toString() const {
        std::string ret;
        
        ret = "PGF:\n";
        ret+= "major version: ";
        ret+= gf::toString(majorVersion);
        ret+= ", minor version: ";
        ret+= gf::toString(minorVersion);
        ret+= "\nflags: (\n";
        for (std::map<std::string, gf::reader::RLiteral*>::const_iterator it = flags.begin(); it != flags.end(); it++) {
            ret+= it->first + ": " + it->second->toString() + "\n";
        }
        ret+= ")\nabstract: (";
        ret+= abstract->toString();
        ret+= ")\nconcretes: (";
        for (std::map<std::string, gf::reader::Concrete*>::const_iterator it = concretes.begin(); it != concretes.end(); it++) {
            ret+= (it == concretes.begin() ? "" : ", ") + it->first;
        }
        ret+= ")";
        
        return ret;
    }
    
}