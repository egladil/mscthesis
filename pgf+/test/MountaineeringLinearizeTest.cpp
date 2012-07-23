//
//  MountaineeringLinearizeTest.cpp
//  pgf+test
//
//  Created by Emil Djupfeldt on 2012-07-23.
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


TEST(MountaineeringLinearize, ILikeThisBeer) {
    gf::Linearizer* linearizer;
    gf::Tree* tree;
    std::string lin;
    
    linearizer = new gf::Linearizer(pgfWithLanguageGuaranteed("Mountaineering.pgf", "MountaineeringEng"), "MountaineeringEng");
    
    tree = parseTree("(PSentence (SProp (PropAction ((ALike IMale) (ThisMass (MassDrink Beer))))))");
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
    
    EXPECT_EQ("I like this beer", lin);
}

