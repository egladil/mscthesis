//
//  IndexedPGFTest.cpp
//  pgf+test
//
//  Created by Emil Djupfeldt on 2012-06-27.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#include <set>
#include <string>
#include <vector>
#include <gtest/gtest.h>

#include <gf/Exception.h>
#include <gf/PGF.h>
#include <gf/PGFBuilder.h>

#include "testutil.h"


TEST(IndexedPGF, IndexedPhrasebookSelect) {
    std::string filename = "PhrasebookIndexed.pgf";
    std::set<std::string> languages;
    gf::PGF* pgf = NULL;
    
    languages.insert("PhrasebookEng");
    languages.insert("PhrasebookFre");
    
    try {
        pgf = gf::PGFBuilder::fromFile(filename, languages);
    } catch (gf::Exception& ex) {
        EXPECT_EQ("", ex.toString());
        FAIL();
    }
    
    EXPECT_NE(pgf, (gf::PGF*) NULL);
    
    EXPECT_TRUE(pgf->hasConcrete("PhrasebookEng"));
    EXPECT_TRUE(pgf->hasConcrete("PhrasebookFre"));
    EXPECT_FALSE(pgf->hasConcrete("PhrasebookIta"));
    
    EXPECT_EQ(pgf->getConcreteNames(), languages);
}


TEST(IndexedPGF, IndexedPhrasebookAll) {
    std::string filename = "PhrasebookIndexed.pgf";
    std::set<std::string> languages;
    gf::PGF* pgf = NULL;
    
    try {
        pgf = gf::PGFBuilder::fromFile(filename);
    } catch (gf::Exception& ex) {
        EXPECT_EQ("", ex.toString());
        FAIL();
    }
    
    EXPECT_NE(pgf, (gf::PGF*) NULL);
    
	EXPECT_TRUE(pgf->hasConcrete("PhrasebookEng"));
	EXPECT_TRUE(pgf->hasConcrete("PhrasebookFre"));
	EXPECT_TRUE(pgf->hasConcrete("PhrasebookIta"));
	
	languages.insert("DisambPhrasebookEng");
	languages.insert("PhrasebookBul");
	languages.insert("PhrasebookCat");
	languages.insert("PhrasebookDan");
	languages.insert("PhrasebookDut");
	languages.insert("PhrasebookEng");
	languages.insert("PhrasebookFre");
	languages.insert("PhrasebookGer");
	languages.insert("PhrasebookIta");
	languages.insert("PhrasebookNor");
	languages.insert("PhrasebookPol");
	languages.insert("PhrasebookRon");
	languages.insert("PhrasebookSpa");
	languages.insert("PhrasebookSwe");
    
	EXPECT_EQ(pgf->getConcreteNames(), languages);
}


TEST(IndexedPGF, UnknownLanguage) {
    std::string filename = "PhrasebookIndexed.pgf";
    std::set<std::string> languages;
    gf::PGF* pgf = NULL;
    
    languages.insert("PhrasebookEng");
    languages.insert("PhrasebookBORK");
    
    try {
        pgf = gf::PGFBuilder::fromFile(filename, languages);
        FAIL();
    } catch (gf::UnknownLanguageException& ex) {
        SUCCEED();
    } catch (gf::Exception& ex) {
        EXPECT_EQ("", ex.toString());
        FAIL();
    }
}


TEST(IndexedPGF, UnindexedFoodsSelect) {
    std::string filename = "Foods.pgf";
    std::set<std::string> languages;
    gf::PGF* pgf = NULL;
    
    languages.insert("FoodsIta");
    
    try {
        pgf = gf::PGFBuilder::fromFile(filename, languages);
    } catch (gf::Exception& ex) {
        EXPECT_EQ("", ex.toString());
        FAIL();
    }
    
    EXPECT_NE(pgf, (gf::PGF*) NULL);
    
	EXPECT_TRUE(pgf->hasConcrete("FoodsIta"));
	EXPECT_FALSE(pgf->hasConcrete("FoodsFre"));
}


TEST(IndexedPGF, UnindexedFoodsAll) {
    std::string filename = "Foods.pgf";
    std::set<std::string> languages;
    gf::PGF* pgf = NULL;
    
    try {
        pgf = gf::PGFBuilder::fromFile(filename);
    } catch (gf::Exception& ex) {
        EXPECT_EQ("", ex.toString());
        FAIL();
    }
    
    EXPECT_NE(pgf, (gf::PGF*) NULL);
    
	EXPECT_TRUE(pgf->hasConcrete("FoodsIta"));
	
	languages.insert("FoodsAfr");
	languages.insert("FoodsAmh");
	languages.insert("FoodsBul");
	languages.insert("FoodsCat");
	languages.insert("FoodsDut");
	languages.insert("FoodsEng");
	languages.insert("FoodsEpo");
	languages.insert("FoodsFas");
	languages.insert("FoodsFin");
	languages.insert("FoodsGer");
	languages.insert("FoodsHeb");
	languages.insert("FoodsHin");
	languages.insert("FoodsIce");
	languages.insert("FoodsIta");
	languages.insert("FoodsJpn");
	languages.insert("FoodsLav");
	languages.insert("FoodsMlt");
	languages.insert("FoodsMon");
	languages.insert("FoodsPor");
	languages.insert("FoodsRon");
	languages.insert("FoodsSwe");
	languages.insert("FoodsTsn");
	languages.insert("FoodsTur");
	languages.insert("FoodsUrd");
    
	EXPECT_EQ(pgf->getConcreteNames(), languages);
}
