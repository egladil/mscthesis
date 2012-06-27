//
//  PGF.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__PGF_h
#define pgf__PGF_h

#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include <set>

#include <gf/RefBase.h>
#include <gf/reader/Abstract.h>
#include <gf/reader/Concrete.h>
#include <gf/reader/RLiteral.h>

namespace gf {
    
    class PGF : public RefBase {
    private:
        uint32_t majorVersion;
        uint32_t minorVersion;
        std::map<std::string, gf::reader::RLiteral*> flags;
        /* final */ gf::reader::Abstract* abstract;
        /* final */ std::map<std::string, gf::reader::Concrete*> concretes;
        
    public:
        /**
         * Create a PGF object.
         * It is the callers responsibility to increase the reference count
         * on any provided objects as the constructor takes ownership of the
         * provided reference. 
         */
        PGF(uint32_t majorVersion, uint32_t minorVersion, const std::map<std::string, gf::reader::RLiteral*>& flags, gf::reader::Abstract* abstract, const std::vector<gf::reader::Concrete*>& concretes);
        virtual ~PGF();
        
        /**
         * Returns the names of all concrete grammars available in the PGF
         * @return list of concrete names
         */
        virtual std::set<std::string> getConcreteNames() const;
        
        /**
         * access the concrete grammar by its name
         * @param name the name of the concrete grammar
         * @return the concrete grammar of null if there is no grammr with
         *             that name.
         */
        virtual gf::reader::Concrete* getConcrete(const std::string& name) const;
        
        /**
         * Get the major version of the pgf.
         * @return major version
         */
        virtual uint32_t getMajorVersion() const;
        
        /**
         * Get the minor version of the pgf.
         * @return minor version
         */
        virtual uint32_t getMinorVersion() const;
        
        /**
         * Get the abstract grammar for the pgf.
         * @return abstract grammar
         */
        virtual gf::reader::Abstract* getAbstract() const;
        
        /**
         * Return true if the given name correspond to a concrete grammar
         * in the pgf, false otherwise.
         * @param name the name of the concrete grammar
         * @return true if the named concrete grammar exists, false otherwise
         */
        virtual bool hasConcrete(const std::string& name) const;
        
        /**
         * Create a string representation of this object.
         * @return a string describing the object.
         */
        virtual std::string toString() const;
    };
    
}


#endif
