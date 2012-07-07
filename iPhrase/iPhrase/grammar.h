//
//  grammar.h
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-07.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef iPhrase_grammar_h
#define iPhrase_grammar_h

#include <string>
#include <gf/PGF.h>

bool loadGrammar(const std::string& filename);
void unloadGrammar();

gf::PGF* getGrammar();

#endif
