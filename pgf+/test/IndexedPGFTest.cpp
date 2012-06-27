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
