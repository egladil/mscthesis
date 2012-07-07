//
//  grammar.cpp
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-07.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#include "grammar.h"

#include <gf/PGFBuilder.h>

gf::PGF* pgf = NULL;

bool loadGrammar(const std::string& filename) {
    gf::PGF* tmp;
    
    if (pgf != NULL) {
        return false;
    }
    
    try {
        tmp = gf::PGFBuilder::fromFile(filename);
    } catch (gf::Exception& e) {
        fprintf(stderr, "Exception while loading %s: %s\n", filename.c_str(), e.toString().c_str());
        return false;
    }
    
    pgf = tmp;
    return true;
}

void unloadGrammar() {
    gf::release(pgf);
}

gf::PGF* getGrammar() {
    return pgf;
}
