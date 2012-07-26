//
//  Generator.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-26.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _Generator_h
#define _Generator_h

#include <stdint.h>
#include <map>
#include <set>
#include <string>
#include <gf/GeneratorException.h>
#include <gf/PGF.h>
#include <gf/RefBase.h>
#include <gf/trees/Absyn.H>

namespace gf {
    
    /**
     * generates a random expression of a given category
     * does not handle dependent categories or categories with implicit arguments
     **/
    class Generator {
    private:
        PGF* pgf;
        std::map<std::string, std::set<std::string> > directRules;
        std::map<std::string, std::set<std::string> > indirectRules;
        
    public:
        Generator(PGF* pgf);
        virtual ~Generator();
        
        virtual Tree* generate() const throw(GeneratorException);
        
        /**
         * generates a category with a random direct rule
         * suitable for simple expressions
         **/
        virtual Tree* getDirect(const std::set<std::string>& dirFuns) const;
        
        /**
         * generates a category with a random indirect rule
         * creates more complex expressions
         **/
        virtual Tree* getIndirect(const std::string& type, const std::set<std::string>& indirFuns) const throw(GeneratorException);
        
        /**
         * generates a random expression of a given category
         * the empirical probability of using direct rules is 60%
         * this decreases the probability of having infinite trees for infinite grammars
         **/
        virtual Tree* generate(const std::string& type) const throw(GeneratorException);
        
        /**
         * generates a number of expressions of a given category
         * the expressions are independent
         * the probability of having simple expressions is higher
         **/
        virtual std::vector<Tree*> generateMany(const std::string& type, uint32_t count) const throw(GeneratorException);
        
        
        /**
         * generates a random string
         **/
        virtual std::string generateString() const;
        
        /**
         * generates a random integer
         **/
        virtual uint32_t generateInt() const;
        
        /**
         * generates a random double
         **/
        virtual double generateDouble() const;
    };
    
}

#endif
