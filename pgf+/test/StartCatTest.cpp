//
//  StartCatTest.cpp
//  pgf+test
//
//  Created by Emil Djupfeldt on 2012-07-26.
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


TEST(StartCat, ThisFreshPizzaIsItalian_Comment) {
    gf::Parser* parser;
    gf::Tree* tree;
    std::string str;
    gf::parser::ParseState* ps;
    std::vector<gf::Tree*> trees;
    std::string parsed, expected;
    
    parser = new gf::Parser(pgfWithLanguageGuaranteed("Foods.pgf", "FoodsEng"), "FoodsEng");
    
    parser->setStartCategory("Comment");
    
    str = "this fresh pizza is Italian";
	tree = parseTree("((Pred (This ((Mod Fresh) Pizza))) Italian)");
    
    ASSERT_NE(tree, (gf::Tree*) NULL);
    
    try {
        ps = parser->parse(str);
    } catch (gf::Exception& e) {
        gf::release(parser);
        throw;
    }
    
    ASSERT_NE(ps, (gf::parser::ParseState*) NULL);
    
    try {
        trees = ps->getTrees();
    } catch (gf::Exception& e) {
        gf::release(ps);
        gf::release(parser);
        throw;
    }
    
    ASSERT_EQ(1, trees.size());
    
    expected = gf::PrintAbsyn().print(tree);
    parsed = gf::PrintAbsyn().print(trees.front());
    
    EXPECT_EQ(parsed, expected);
    
    delete trees.front();
    delete tree;
    
    gf::release(ps);
    gf::release(parser);
}


TEST(StartCat, ThoseBoringFishAreExpensive_Comment) {
    gf::Parser* parser;
    gf::Tree* tree;
    std::string str;
    gf::parser::ParseState* ps;
    std::vector<gf::Tree*> trees;
    std::string parsed, expected;
    
    parser = new gf::Parser(pgfWithLanguageGuaranteed("Foods.pgf", "FoodsEng"), "FoodsEng");
    
    parser->setStartCategory("Comment");
    
    str = "those boring fish are expensive";
	tree = parseTree("((Pred (Those ((Mod Boring) Fish))) Expensive)");
    
    ASSERT_NE(tree, (gf::Tree*) NULL);
    
    try {
        ps = parser->parse(str);
    } catch (gf::Exception& e) {
        gf::release(parser);
        throw;
    }
    
    ASSERT_NE(ps, (gf::parser::ParseState*) NULL);
    
    try {
        trees = ps->getTrees();
    } catch (gf::Exception& e) {
        gf::release(ps);
        gf::release(parser);
        throw;
    }
    
    ASSERT_EQ(1, trees.size());
    
    expected = gf::PrintAbsyn().print(tree);
    parsed = gf::PrintAbsyn().print(trees.front());
    
    EXPECT_EQ(parsed, expected);
    
    delete trees.front();
    delete tree;
    
    gf::release(ps);
    gf::release(parser);
}


TEST(StartCat, ThisFreshPizza_Item) {
    gf::Parser* parser;
    gf::Tree* tree;
    std::string str;
    gf::parser::ParseState* ps;
    std::vector<gf::Tree*> trees;
    std::string parsed, expected;
    
    parser = new gf::Parser(pgfWithLanguageGuaranteed("Foods.pgf", "FoodsEng"), "FoodsEng");
    
    parser->setStartCategory("Item");
    
    str = "this fresh pizza";
	tree = parseTree("(This ((Mod Fresh) Pizza))");
    
    ASSERT_NE(tree, (gf::Tree*) NULL);
    
    try {
        ps = parser->parse(str);
    } catch (gf::Exception& e) {
        gf::release(parser);
        throw;
    }
    
    ASSERT_NE(ps, (gf::parser::ParseState*) NULL);
    
    try {
        trees = ps->getTrees();
    } catch (gf::Exception& e) {
        gf::release(ps);
        gf::release(parser);
        throw;
    }
    
    ASSERT_EQ(1, trees.size());
    
    expected = gf::PrintAbsyn().print(tree);
    parsed = gf::PrintAbsyn().print(trees.front());
    
    EXPECT_EQ(parsed, expected);
    
    delete trees.front();
    delete tree;
    
    gf::release(ps);
    gf::release(parser);
}


TEST(StartCat, ThoseBoringFish_Item) {
    gf::Parser* parser;
    gf::Tree* tree;
    std::string str;
    gf::parser::ParseState* ps;
    std::vector<gf::Tree*> trees;
    std::string parsed, expected;
    
    parser = new gf::Parser(pgfWithLanguageGuaranteed("Foods.pgf", "FoodsEng"), "FoodsEng");
    
    parser->setStartCategory("Item");
    
    str = "those boring fish";
	tree = parseTree("(Those ((Mod Boring) Fish))");
    
    ASSERT_NE(tree, (gf::Tree*) NULL);
    
    try {
        ps = parser->parse(str);
    } catch (gf::Exception& e) {
        gf::release(parser);
        throw;
    }
    
    ASSERT_NE(ps, (gf::parser::ParseState*) NULL);
    
    try {
        trees = ps->getTrees();
    } catch (gf::Exception& e) {
        gf::release(ps);
        gf::release(parser);
        throw;
    }
    
    ASSERT_EQ(1, trees.size());
    
    expected = gf::PrintAbsyn().print(tree);
    parsed = gf::PrintAbsyn().print(trees.front());
    
    EXPECT_EQ(parsed, expected);
    
    delete trees.front();
    delete tree;
    
    gf::release(ps);
    gf::release(parser);
}
