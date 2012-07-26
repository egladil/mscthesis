//
//  FoodsPredictTest.cpp
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


TEST(FoodsPredict, FoodsEng) {
    gf::Parser* parser;
    gf::Tree* tree;
    std::string str;
    gf::parser::ParseState* ps;
    std::set<std::string> predictions;
    std::set<std::string> expected;
    
    parser = new gf::Parser(pgfWithLanguageGuaranteed("Foods.pgf", "FoodsEng"), "FoodsEng");
    
    ASSERT_NE(tree, (gf::Tree*) NULL);
    
    try {
        ps = parser->parse();
    } catch (gf::Exception& e) {
        gf::release(parser);
        throw;
    }
    
    ASSERT_NE(ps, (gf::parser::ParseState*) NULL);
    
    try {
        predictions = ps->predict();
    } catch (gf::Exception& e) {
        gf::release(ps);
        gf::release(parser);
        throw;
    }
    
    expected.insert("that");
    expected.insert("this");
    expected.insert("these");
    expected.insert("those");
    
    EXPECT_EQ(predictions, expected);
    
    gf::release(ps);
    gf::release(parser);
}


TEST(FoodsPredict, FoodsSwe) {
    gf::Parser* parser;
    gf::Tree* tree;
    std::string str;
    gf::parser::ParseState* ps;
    std::set<std::string> predictions;
    std::set<std::string> expected;
    
    parser = new gf::Parser(pgfWithLanguageGuaranteed("Foods.pgf", "FoodsSwe"), "FoodsSwe");
    
    ASSERT_NE(tree, (gf::Tree*) NULL);
    
    try {
        ps = parser->parse();
    } catch (gf::Exception& e) {
        gf::release(parser);
        throw;
    }
    
    ASSERT_NE(ps, (gf::parser::ParseState*) NULL);
    
    try {
        predictions = ps->predict();
    } catch (gf::Exception& e) {
        gf::release(ps);
        gf::release(parser);
        throw;
    }
    
    expected.insert("de");
    expected.insert("den");
    expected.insert("det");
    
    EXPECT_EQ(predictions, expected);
    
    gf::release(ps);
    gf::release(parser);
}


TEST(FoodsPredict, FoodsIta) {
    gf::Parser* parser;
    gf::Tree* tree;
    std::string str;
    gf::parser::ParseState* ps;
    std::set<std::string> predictions;
    std::set<std::string> expected;
    
    parser = new gf::Parser(pgfWithLanguageGuaranteed("Foods.pgf", "FoodsIta"), "FoodsIta");
    
    ASSERT_NE(tree, (gf::Tree*) NULL);
    
    try {
        ps = parser->parse();
    } catch (gf::Exception& e) {
        gf::release(parser);
        throw;
    }
    
    ASSERT_NE(ps, (gf::parser::ParseState*) NULL);
    
    try {
        predictions = ps->predict();
    } catch (gf::Exception& e) {
        gf::release(ps);
        gf::release(parser);
        throw;
    }
    
    expected.insert("quei");
    expected.insert("quel");
    expected.insert("quella");
    expected.insert("quelle");
    expected.insert("questa");
    expected.insert("queste");
    expected.insert("questi");
    expected.insert("questo");
    
    EXPECT_EQ(predictions, expected);
    
    gf::release(ps);
    gf::release(parser);
}


