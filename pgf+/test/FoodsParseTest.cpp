//
//  FoodsParseTest.cpp
//  pgf+test
//
//  Created by Emil Djupfeldt on 2012-07-05.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//


#include <set>
#include <string>
#include <vector>
#include <gtest/gtest.h>

#include <gf/Exception.h>
#include <gf/Parser.h>
#include <gf/ParseException.h>
#include <gf/PGF.h>
#include <gf/PGFBuilder.h>
#include <gf/trees/Absyn.H>
#include <gf/trees/Printer.h>

#include "testutil.h"


TEST(FoodsParse, ThisFreshPizzaIsItalian) {
    gf::Parser* parser;
    gf::Tree* tree;
    std::string str;
    gf::parser::ParseState* ps;
    std::vector<gf::Tree*> trees;
    std::string parsed, expected;
    
    parser = new gf::Parser(pgfWithLanguageGuaranteed("Foods.pgf", "FoodsEng"), "FoodsEng");
    
    str = "this fresh pizza is Italian";
	tree = parseTree("((Pred (This ((Mod Fresh) Pizza))) Italian)");
    
    EXPECT_NE(tree, (gf::Tree*) NULL);
    
    try {
        ps = parser->parse(str);
    } catch (gf::Exception& e) {
        gf::release(parser);
        throw;
    }
    
    EXPECT_NE(ps, (gf::parser::ParseState*) NULL);
     
    try {
        trees = ps->getTrees();
    } catch (gf::Exception& e) {
        gf::release(ps);
        gf::release(parser);
        throw;
    }
    
    EXPECT_EQ(1, trees.size());
    
    expected = gf::PrintAbsyn().print(tree);
    parsed = gf::PrintAbsyn().print(trees.front());
    
    EXPECT_EQ(parsed, expected);
    
    delete trees.front();
    delete tree;
    
    gf::release(ps);
    gf::release(parser);
}
