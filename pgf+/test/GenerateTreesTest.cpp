//
//  GenerateTreesTest.cpp
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
#include <gf/GenerateTrees.h>
#include <gf/ParseException.h>
#include <gf/PGF.h>
#include <gf/PGFBuilder.h>
#include <gf/trees/Absyn.H>
#include <gf/trees/Printer.h>

#include "testutil.h"


TEST(GenerateTrees, Quality) {
    gf::GenerateTrees* generator;
    std::vector<gf::Tree*> trees;
    std::set<std::string> generated;
    std::set<std::string> expected;
    
    generator = new gf::GenerateTrees(pgfWithLanguageGuaranteed("Foods.pgf", "FoodsEng"));
    
    trees = generator->generateTrees("Quality", 1);
    
    for (std::vector<gf::Tree*>::iterator it = trees.begin(); it != trees.end(); it++) {
        generated.insert(gf::PrintAbsyn().print(*it));
        delete *it;
    }
    
    expected.insert("(Very Boring) ");
    expected.insert("(Very Delicious) ");
    expected.insert("(Very Expensive) ");
    expected.insert("(Very Fresh) ");
    expected.insert("(Very Italian) ");
    expected.insert("(Very Warm) ");
    expected.insert("Boring ");
    expected.insert("Delicious ");
    expected.insert("Expensive ");
    expected.insert("Fresh ");
    expected.insert("Italian ");
    expected.insert("Warm ");
    
    EXPECT_EQ(generated, expected);
    
    gf::release(generator);
}
