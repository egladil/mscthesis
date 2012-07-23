//
//  Linearizer.h
//  
//
//  Created by Emil Djupfeldt on 2012-06-28.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _Linearizer_h
#define _Linearizer_h

#include <stdint.h>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <gf/LinearizerException.h>
#include <gf/PGF.h>
#include <gf/RefBase.h>
#include <gf/linearizer/AppResult.h>
#include <gf/linearizer/BracketedToken.h>
#include <gf/linearizer/CncType.h>
#include <gf/linearizer/LinTriple.h>
#include <gf/linearizer/RezDesc.h>
#include <gf/reader/Concrete.h>
#include <gf/reader/Production.h>
#include <gf/reader/Type.h>
#include <gf/trees/Absyn.H>

namespace gf {
    
    class Linearizer : public RefBase {
    private:
        typedef std::map<uint32_t, gf::reader::ProductionPointerSet> MapIntSP;
        typedef std::map<std::string, MapIntSP> MapStrMapIntSP;
        typedef std::vector<gf::linearizer::BracketedToken*> VBracketedToken;
        typedef std::vector<VBracketedToken> VVBracketedToken;
        typedef std::vector<VVBracketedToken> VVVBracketedToken;
        
    private:
        PGF* pgf;
        gf::reader::Concrete* concrete;
        MapStrMapIntSP lProductions;
        
        /**
         * constructs the l-productions of the concrete syntax for
         * a given language
         **/
        MapStrMapIntSP getLProductions() const throw (gf::LinearizerException);
        
        /**
         * aligns the indexes for the l-productions
         **/
        MapStrMapIntSP linIndex(const MapIntSP& productions) const;
        
        /** This function computes the list of abstract function corresponding to
         * a given production. This is easy for standard productions but less for
         * coercions because then you have to search reccursively.
         * @param p the production
         * @param productions ???
         **/
        std::vector<std::string> getFunctions(gf::reader::Production* production, const MapIntSP& productions) const;
        
        /**
         * checks if index is the index of a literal or a valid set of productions
         **/
        bool conditionProd(uint32_t index, const MapIntSP& productions) const;
        
        /**
         * filters a set of productions according to filterRule
         **/
        gf::reader::ProductionPointerSet filterProdSet1(const MapIntSP& productions, const gf::reader::ProductionPointerSet& set) const;
        
        /**
         * filters an IntMap of productions according to filterProdsSet1
         **/
        MapIntSP filterProductions(const MapIntSP& productions0, const MapIntSP& productions) const;
        
        /**
         * checks if a production satisfies conditionProd recursively
         **/
        bool filterRule(const MapIntSP& productions, gf::reader::Production* production) const;
        
        /**
         * checks if a production just has a variable argument
         **/
        bool isHoProduction(gf::reader::Production* production) const;
        
        /**
         * gets list of forest ids from the categories in ho_cats
         **/
        std::set<uint32_t> getHoFIds() const;
        
        /**
         * get all names of types from Concrete
         **/
        std::set<std::string> getHoCategories() const;
        
        /**
         * gets the types from the hypotheses of a type
         **/
        std::vector<std::string> getHypoArgsOfType(gf::reader::Type* type) const;
        
        /**
         * flattens a bracketed token
         **/
        std::vector<std::string> untoken(gf::linearizer::BracketedToken* bt, const std::string& after) const;
        
        /**
         * flattens the result of the linearization
         **/
        std::vector<std::string> renderLin(gf::linearizer::LinTriple* triple) const;
        
        std::vector<std::vector<std::string> > renderAllLins(const std::vector<gf::linearizer::LinTriple*>& triples) const;
        
        std::vector<gf::linearizer::LinTriple*> linearize(const Tree* tree) const throw (gf::LinearizerException);
        
        /**
         * main linearization function
         * @param xs is the list of bound variables (from lambdas)
         * @param ys
         * @param mb_cty
         * @param mb_fid
         * @param tree is the tree to linearize
         * @return all the possible linearized tuples for this tree.
         **/
        std::vector<gf::linearizer::LinTriple*> lin0(std::vector<std::string>& xs, const std::vector<std::string>& ys, gf::linearizer::CncType* mb_cty, uint32_t mb_fid, const Tree* tree) const throw (gf::LinearizerException);
        
        /**
         * intermediate linearization for complex expressions
         * Linearize function appliction.
         * To linearize the application of the function "f" to the arguments
         * (trees) a, b and c use :
         * apply(???,???,??? "f", [a,b,c])
         *
         * 'apply' will linearize the argument and then use the concrete function
         * for "f" to glue them together.
         * @param xs
         * @param mb_cty
         * @param n_fid
         * @param f the name of the function to be applied
         * @param es the argument of the function to linearize
         * @return All the possible linearization for the application of f to es
         **/
        std::vector<gf::linearizer::LinTriple*> apply(const std::vector<std::string>& xs, gf::linearizer::CncType* mb_cty, uint32_t n_fid, const std::string& function, const std::vector<const Tree*>& trees) const throw (gf::LinearizerException);
        
        std::vector<gf::linearizer::AppResult*> getApps(const MapIntSP& productions, gf::linearizer::CncType* mb_cty, const std::string& function) const throw (gf::LinearizerException);
        
        std::vector<gf::linearizer::AppResult*> toApp(gf::linearizer::CncType* cty, gf::reader::Production* production, const std::string& function, const MapIntSP& productions) const throw (gf::LinearizerException);
        
        /**
         * computes the types of the arguments of a function type
         **/
        std::vector<std::string> catSkeleton(gf::reader::Type* type) const;
        
        /**
         * creates a simple vector of vectors of bracketed tokens containing a string value
         **/
        VVBracketedToken mkVVBracketedToken(const std::string& str) const;
        
        /**
         * computes the sequence of bracketed tokens associated to a symbol
         **/
        VBracketedToken compute(gf::reader::Symbol* symbol, const std::vector<gf::linearizer::CncType*>& cncTypes, const VVVBracketedToken& linTables) const;
        
        /**
         * retrieves a sequence of bracketed tokens from an intermediate result of the linearization
         * according to 2 indices from a production
         **/
        VBracketedToken getArg(uint32_t d, uint32_t r, const std::vector<gf::linearizer::CncType*>& cncTypes, const VVVBracketedToken& linTables) const;
        
        /**
         * computes a sequence of bracketed tokens from the sequence of symbols of a concrete function
         **/
        VBracketedToken computeSequence(gf::reader::Sequence* sequence, const std::vector<gf::linearizer::CncType*>& cncTypes, const VVVBracketedToken& linTables) const;
        
        /**
         * shuffles the results of of the intermediate linearization,
         * for generating all the possible combinations
         **/
        std::vector<gf::linearizer::RezDesc*> descend(uint32_t n_fid, std::list<gf::linearizer::CncType*>& cncTypes, std::list<const Tree*>& trees, const std::vector<std::string>& xs) const throw (gf::LinearizerException);
        
        /**
         * checks if a production is application production
         **/
        bool isApplication(gf::reader::Production* production) const;
        
        /**
         * checks if an integer is the index of an integer literal
         **/
        bool isLiteralInt(int32_t i) const;
        
        /**
         * checks if an integer is the index of a string literal
         **/
        bool isLiteralString(int32_t i) const;
        
        /**
         * checks if an integer is the index of a float literal
         **/
        bool isLiteralFloat(int32_t i) const;
        
        /**
         * checks if an integer is the index of a variable literal
         **/
        bool isLiteralVar(int32_t i) const;
        
        /**
         * checks if an integer is the index of a literal
         **/
        bool isLiteral(int32_t i) const;
        
        
    public:
        /** linearizes an expression to a bracketed token
         * and further on to a string
         * not implemented to dependent categories, implicit argument,
         * and higher-order abstract syntax
         * @param pgf the pgf object that contains the concrete grammar.
         * @param concrete the concrete grammar to use.
         **/
        Linearizer(PGF* pgf, gf::reader::Concrete* concrete) throw (gf::LinearizerException);
        
        /** linearizes an expression to a bracketed token
         * and further on to a string
         * not implemented to dependent categories, implicit argument,
         * and higher-order abstract syntax
         * @param pgf the pgf object that contains the concrete grammar.
         * @param concrete the name of the concrete grammar to use.
         **/
        Linearizer(PGF* pgf, const std::string& concrete) throw (gf::LinearizerException);
        
        virtual ~Linearizer();
        
        
        /**
         * Linearize a tree to a vector of tokens.
         **/
        virtual std::vector<std::string> linearizeTokens(const Tree* absyn) const throw (gf::LinearizerException);
        
        /**
         * Linearize a tree to a string.
         **/
        virtual std::string linearizeString(const Tree* absyn) const throw (gf::LinearizerException);
    };
    
}

#endif
