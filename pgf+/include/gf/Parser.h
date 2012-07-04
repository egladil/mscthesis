//
//  Parser.h
//  
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef _Parser_h
#define _Parser_h

#include <string>
#include <vector>
#include <gf/PGF.h>
#include <gf/ParseException>
#include <gf/RefBase.h>
#include <gf/UnknownLanguageException.h>
#include <gf/parser/ParseState.h>
#include <gf/reader/Concrete.h>
#include <gf/trees/Absyn.H>

namespace gf {
    
    class Parser : public RefBase {
    private:
        gf::reader::Concrete* language;
        std::string startcat;
        
    public:
        Parser(PGF* pgf, gf::reader::Concrete* language);
        Parser(PGF* pgf, const std::string& language) throw (UnknownLanguageException);
        virtual ~Parser();
        
        virtual void setStartCategory(const std::string& startcat);
        virtual const std::string& getStartCategory() const;
        
        /**
         * Parse the given list of tokens
         * @param tokens the input tokens
         * @return the corresponding parse-state
         **/
        virtual gf::parser::ParseState* parse(const std::vector<std::string>& tokens) const throw (ParseException);
        
        /**
         * Parse the given list of tokens
         * @param tokens the input tokens
         * @return a vector of trees
         **/
        virtual std::vector<Tree*> parseToTrees(const std::vector<std::string>& tokens) const throw (ParseException);
        
        /**
         * Parse the given string
         * uses a very basic tokenizer that split on whitespaces.
         * @param phrase the input string
         * @return the corresponding parse-state
         **/
        virtual gf::parser::ParseState* parse(const std::string& phrase) const throw (ParseException);
        
        /**
         * Parses the empty string
         * (usefull for completion)
         * @return the corresponding parse-state
         **/
        virtual gf::parser::ParseState* parse() const throw (ParseException);

    };
    
}

#endif
