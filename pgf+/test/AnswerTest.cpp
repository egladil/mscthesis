//
//  AnswerTest.cpp
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
#include <gf/Linearizer.h>
#include <gf/LinearizerException.h>
#include <gf/PGF.h>
#include <gf/PGFBuilder.h>
#include <gf/trees/Absyn.H>

#include "testutil.h"


TEST(Answer, TakeBus10FromValandToChalmersAt1) {
    gf::Linearizer* linearizer;
    gf::Tree* tree;
    std::string lin;
    std::set<std::string> expected;
    
    linearizer = new gf::Linearizer(pgfWithLanguageGuaranteed("Answer.pgf", "AnswerEng"), "AnswerEng");
    
    tree = parseTree("((((Routing Bus) St_1) St_0) N1)");
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
    
	expected.insert("Take bus 10 from Valand to Chalmers at 1");
	expected.insert("Take bus 10 from Valand Göteborg to Chalmers at 1");
	expected.insert("Take bus 10 from Valand to Chalmers Göteborg at 1");
	expected.insert("Take bus 10 from Valand Göteborg to Chalmers Göteborg at 1");
    
    for (std::set<std::string>::const_iterator it = expected.begin(); it != expected.end(); it++) {
        if (lin == *it) {
            SUCCEED();
            return;
        }
    }
    
    EXPECT_EQ(lin, *expected.begin());
}
