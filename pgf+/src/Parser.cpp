//
//  Parser.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-04.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/Parser.h>
#include <gf/stringutil.h>

namespace gf {
    
    Parser::Parser(PGF* pgf, gf::reader::Concrete* language)
        : language(language), startcat(pgf->getAbstract()->startcat()) {
        gf::release(pgf);
    }
    
    Parser::Parser(PGF* pgf, const std::string& language) throw (UnknownLanguageException)
        : language(pgf->getConcrete(language)), startcat(pgf->getAbstract()->startcat()) {
        this->language->addReference();
        gf::release(pgf);
    }
    
    Parser::~Parser() {
        gf::release(language);
    }
    
    void Parser::setStartCategory(const std::string& startcat) {
        this->startcat = startcat;
    }
    
    const std::string& Parser::getStartCategory() const {
        return startcat;
    }
    
    gf::parser::ParseState* Parser::parse(const std::vector<std::string>& tokens) const throw (ParseException) {
        gf::parser::ParseState* state;
        
        language->addReference();
        state = new gf::parser::ParseState(language, startcat);
        
        for (std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); it++) {
            try {
                if (!state->scan(*it)) {
                    break;
                }
            } catch (ParseException& e) {
                gf::release(state);
                throw;
            }
        }
        
        return state;
    }
    
    std::vector<Tree*> Parser::parseToTrees(const std::vector<std::string>& tokens) const throw (ParseException) {
        gf::parser::ParseState* state;
        std::vector<Tree*> ret;
        
        state = parse(tokens);
        ret = state->getTrees();
        
        gf::release(state);
        return ret;
    }
    
    gf::parser::ParseState* Parser::parse(const std::string& phrase) const throw (ParseException) {
        return parse(split(phrase, ' '));
    }
    
    gf::parser::ParseState* Parser::parse() const throw (ParseException) {
        return parse(std::vector<std::string>());
    }
    
}
