//
//  FoodsLinearizeTest.cpp
//  pgf+test
//
//  Created by Emil Djupfeldt on 2012-06-28.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#include <set>
#include <string>
#include <vector>
#include <gtest/gtest.h>

#include <gf/Exception.h>
#include <gf/Linearizer.h>
#include <gf/LinearizerException.h>
#include <gf/PGF.h>
#include <gf/PGFBuilder.h>
#include <gf/trees/Absyn.H>

#include "testutil.h"


TEST(FoodsLinearize, ThisFreshPizzaIsItalian) {
    gf::Linearizer* linearizer;
    gf::Tree* tree;
    std::string lin;
    
    linearizer = new gf::Linearizer(pgfWithLanguageGuaranteed("Foods.pgf", "FoodsEng"), "FoodsEng");
    
    tree = parseTree("((Pred (This ((Mod Fresh) Pizza))) Italian)");
    try {
        lin = linearizer->linearizeString(tree);
    } catch (gf::Exception& ex) {
        delete tree;
        gf::release(linearizer);
        
        EXPECT_EQ("", ex.toString());
        FAIL();
    }
    
    delete tree;
    gf::release(linearizer);
    
    EXPECT_EQ(lin, "this fresh pizza is Italian");
}


TEST(FoodsLinearize, ThoseBoringFishAreExpensive) {
    gf::Linearizer* linearizer;
    gf::Tree* tree;
    std::string lin;
    
    linearizer = new gf::Linearizer(pgfWithLanguageGuaranteed("Foods.pgf", "FoodsEng"), "FoodsEng");
    
    tree = parseTree("((Pred (Those ((Mod Boring) Fish))) Expensive)");
    try {
        lin = linearizer->linearizeString(tree);
    } catch (gf::Exception& ex) {
        delete tree;
        gf::release(linearizer);
        
        EXPECT_EQ("", ex.toString());
        FAIL();
    }
    
    delete tree;
    gf::release(linearizer);
    
    EXPECT_EQ(lin, "those boring fish are expensive");
}


TEST(FoodsLinearize, ThisDeliciousPizzaIsFresh_swe) {
    gf::Linearizer* linearizer;
    gf::Tree* tree;
    std::string lin;
    
    linearizer = new gf::Linearizer(pgfWithLanguageGuaranteed("Foods.pgf", "FoodsSwe"), "FoodsSwe");
    
    tree = parseTree("((Pred (This ((Mod Delicious) Pizza))) Fresh)");
    try {
        lin = linearizer->linearizeString(tree);
    } catch (gf::Exception& ex) {
        delete tree;
        gf::release(linearizer);
        
        EXPECT_EQ("", ex.toString());
        FAIL();
    }
    
    delete tree;
    gf::release(linearizer);
    
    EXPECT_EQ(lin, "den här läckra pizzan är färsk");
}


TEST(FoodsLinearize, ThisDeliciousPizzaIsFresh_ita) {
    gf::Linearizer* linearizer;
    gf::Tree* tree;
    std::string lin;
    
    linearizer = new gf::Linearizer(pgfWithLanguageGuaranteed("Foods.pgf", "FoodsIta"), "FoodsIta");
    
    tree = parseTree("((Pred (This ((Mod Delicious) Pizza))) Fresh)");
    try {
        lin = linearizer->linearizeString(tree);
    } catch (gf::Exception& ex) {
        delete tree;
        gf::release(linearizer);
        
        EXPECT_EQ("", ex.toString());
        FAIL();
    }
    
    delete tree;
    gf::release(linearizer);
    
    EXPECT_EQ(lin, "questa pizza deliziosa è fresca");
}

