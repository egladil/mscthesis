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
#include <gf/trees/Parser.H>

#include "testutil.h"


static gf::PGF* pgfWithLanguageGuaranteed(const std::string& file, const std::string& language) {
    std::string filename = getAppDir() + file;
    std::set<std::string> languages;
    gf::PGF* pgf = NULL;
    
    languages.insert(language);
    
    try {
        pgf = gf::PGFBuilder::fromFile(filename, languages);
    } catch (gf::Exception& ex) {
        EXPECT_EQ("", ex.toString());
        EXPECT_EQ(0, 1);
        return NULL;
    }
    
    EXPECT_NE(pgf, (gf::PGF*) NULL);
    
    EXPECT_TRUE(pgf->hasConcrete(language));
    
    return pgf;
}

static gf::Tree* parseTree(const std::string& str) {
    return gf::pTree(str.c_str());
}


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
    
    usleep(10 * 1000000);
    
    EXPECT_EQ(lin, "this fresh pizza is Italian");
}

