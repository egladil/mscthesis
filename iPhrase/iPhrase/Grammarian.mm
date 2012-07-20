//
//  Grammarian.m
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-11.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import "Grammarian.h"
#include "grammar.h"
#include "iso639.h"
#include <gf/Parser.h>
#include <gf/Linearizer.h>
#include <gf/trees/Printer.H>
#include <algorithm>
#include <stdlib.h>


static int calcEditDistance(NSString* a, NSString* b) {
    size_t aLen = [a length];
    size_t bLen = [b length];
    unichar aChars[aLen];
    unichar bChars[bLen];
    int distance[aLen + 1][bLen + 1];
    
    
    for (int i = 0; i < aLen; i++) {
        aChars[i] = [a characterAtIndex:i];
    }
    
    for (int i = 0; i < bLen; i++) {
        bChars[i] = [b characterAtIndex:i];
    }
    
    
    for (int i = 0; i <= aLen; i++) {
        distance[i][0] = i;
    }
    
    for (int i = 0; i <= bLen; i++) {
        distance[0][i] = i;
    }
    
    
    for (int i = 0; i < aLen; i++) {
        for (int j = 0; j < bLen; j++) {
            int cost;
            int dist;
            
            cost = (aChars[i] == bChars[j]) ? 0 : 1;
            
            dist = distance[i][j] + cost;
            dist = std::min(dist, distance[i + 1][j] + 1);
            dist = std::min(dist, distance[i][j + 1] + 1);
            
            if (i > 0 && j > 0 && aChars[i - 1] == bChars[j] && aChars[i] == bChars[i - 1]) {
                dist = std::min(dist, distance[i - 1][j - 1] + cost);
            }
            
            distance[i + 1][j + 1] = dist;
        }
    }
    
    
    return distance[aLen][bLen];
}


@implementation Grammarian
{
    gf::reader::Concrete* sourceConcrete;
    gf::Parser* parser;
    gf::parser::ParseState* state;
    std::set<std::string> predictions;
    int acceptedTokenCount;
}

- (id)initWithGrammar:(gf::PGF*)pgf withLanguage:(gf::reader::Concrete*)concrete {
    self = [super init];
    
    if (concrete == NULL) {
        return nil;
    }
    
    sourceConcrete = concrete;
    
    concrete->addReference();
    parser = new gf::Parser(pgf, concrete);
    
    try {
        state = parser->parse();
    } catch (gf::Exception& e) {
        return nil;
    }
    
    predictions = state->predict();
    
    acceptedTokenCount = 0;
    
    return self;
}

- (id)init {
    gf::PGF* pgf;
    gf::reader::Concrete* concrete;
    
    pgf = getGrammar();
    if (pgf == NULL) {
        return nil;
    }
    
    concrete = pgf->getConcrete(pgf->getAbstract()->getName() + "Eng");
    if (concrete == NULL) {
        std::set<std::string> langs;
        
        langs = pgf->getConcreteNames();
        if (langs.empty()) {
            return nil;
        }
        
        concrete = pgf->getConcrete(*langs.begin());
        assert(concrete != NULL);
    }
    
    pgf->addReference();
    concrete->addReference();
    return [self initWithGrammar:pgf withLanguage:concrete];
}

- (id)initWithLanguage:(NSString*)language {
    gf::PGF* pgf;
    gf::reader::Concrete* concrete;
    
    pgf = getGrammar();
    if (pgf == NULL) {
        return nil;
    }

    concrete = pgf->getConcrete([language UTF8String]);
    if (concrete == NULL) {
        return nil;
    }
    
    pgf->addReference();
    concrete->addReference();
    return [self initWithGrammar:pgf withLanguage:concrete];
}

- (void)dealloc {
    gf::release(sourceConcrete);
    gf::release(parser);
    gf::release(state);
}

+ (NSArray*)languages {
    gf::PGF* pgf;
    NSMutableArray* ret;
    std::set<std::string> langs;
    
    pgf = getGrammar();
    if (pgf == NULL) {
        return nil;
    }
    
    ret = [[NSMutableArray alloc] init];
    
    langs = pgf->getConcreteNames();
    for (std::set<std::string>::const_iterator it = langs.begin(); it != langs.end(); it++) {
        [ret addObject:[NSString stringWithUTF8String:it->c_str()]];
    }
    
    return ret;
}

+ (NSString*) codeForLanguage:(NSString*)language {
    gf::PGF* pgf;
    std::set<std::string> langs;
    std::string prefix;
    std::string lang;
    
    if ([language length] == 0) {
        return nil;
    }
    
    pgf = getGrammar();
    if (pgf == NULL) {
        return nil;
    }
    
    prefix = pgf->getAbstract()->getName();
    lang = [language UTF8String];
    
    if (lang.substr(0, prefix.size()) == prefix) {
        return [[NSString stringWithUTF8String:lang.substr(prefix.size()).c_str()] lowercaseString];
    }
    
    return nil;
}

+ (NSString*) languageForCode:(NSString*)code {
    gf::PGF* pgf;
    std::string lang;
    
    if ([code length] == 0) {
        return nil;
    }
    
    pgf = getGrammar();
    if (pgf == NULL) {
        return nil;
    }
    
    lang = pgf->getAbstract()->getName() + [[[code substringToIndex:1] uppercaseString] UTF8String] + [[[code substringFromIndex:1] lowercaseString] UTF8String];
    
    if (pgf->getConcrete(lang) != NULL) {
        return [NSString stringWithUTF8String:lang.c_str()];
    }
    
    return nil;
}

+ (NSString*) humanReadableNameOfLanguageFromCode:(NSString*)code {
    info_t* info;
    
    info = getLanguageInfo([code UTF8String]);
    if (info == NULL || info->name == NULL || info->name[0] == 0) {
        return [Grammarian languageForCode:code];
    }
    
    return [NSString stringWithUTF8String:info->name];
}

+ (NSString*) humanReadableNameOfLanguage:(NSString*)language {
    NSString* code;
    
    code = [Grammarian codeForLanguage:language];
    if (code == nil) {
        return language;
    }
    
    return [Grammarian humanReadableNameOfLanguageFromCode:code];
}

- (NSString*) sourceLanguage {
    return [NSString stringWithUTF8String: sourceConcrete->getName().c_str()];
}


- (NSArray*)predict:(NSString*)prefix {
    std::string pre;
    NSMutableArray* ret;
    
    pre = [prefix UTF8String];
    ret = [[NSMutableArray alloc] init];
    for (std::set<std::string>::const_iterator it = predictions.begin(); it != predictions.end(); it++) {
        std::string str = *it;
        
        if (str.substr(0, pre.size()) == pre) {
            [ret addObject:[NSString stringWithUTF8String:str.c_str()]];
        }
    }
    
    return ret;
}

- (NSArray*)predict:(NSString*)prefix withEditDistance:(int)distance {
    std::string pre;
    NSMutableArray* ret;
    
    pre = [prefix UTF8String];
    ret = [[NSMutableArray alloc] init];
    for (std::set<std::string>::const_iterator it = predictions.begin(); it != predictions.end(); it++) {
        std::string str = *it;
        NSString* add = [NSString stringWithUTF8String:str.c_str()];
        
        if (str.substr(0, pre.size()) == pre || calcEditDistance(prefix, add) <= distance) {
            [ret addObject:add];
        }
    }
    
    return ret;
}

- (NSArray*)match:(NSString*)token withEditDistance:(int)distance {
    NSMutableArray* ret;
    
    ret = [[NSMutableArray alloc] init];
    for (std::set<std::string>::const_iterator it = predictions.begin(); it != predictions.end(); it++) {
        NSString* add = [NSString stringWithUTF8String:it->c_str()];
        
        if (calcEditDistance(token, add) <= distance) {
            [ret addObject:add];
        }
    }
    
    return ret;
}

- (NSArray*)matchIgnoringCase:(NSString*)token {
    NSMutableArray* ret;
    
    token = [token lowercaseString];
    ret = [[NSMutableArray alloc] init];
    for (std::set<std::string>::const_iterator it = predictions.begin(); it != predictions.end(); it++) {
        NSString* add = [NSString stringWithUTF8String:it->c_str()];
        
        if ([token compare:[add lowercaseString]] == NSOrderedSame) {
            [ret addObject:add];
        }
    }
    
    return ret;
}


- (BOOL)accept:(NSString*)token {
    if (!state->scan([token UTF8String])) {
        return FALSE;
    }
    
    acceptedTokenCount++;
    predictions = state->predict();
    
    return TRUE;
}

- (void)reset {
    gf::release(state);
    state = parser->parse();
    predictions = state->predict();
    acceptedTokenCount = 0;
}

- (int) acceptedTokenCount {
    return acceptedTokenCount;
}


- (NSArray*) parseTrees {
    std::vector<gf::Tree*> trees;
    NSMutableArray* ret;
    std::set<std::string> deduplicate;
    
    try {
        trees = state->getTrees();
    } catch (gf::Exception& e) {
        return nil;
    }
    
    ret = [[NSMutableArray alloc] init];
    
    for (std::vector<gf::Tree*>::iterator it = trees.begin(); it != trees.end(); it++) {
        gf::Tree* tree = *it;
        char* buf;
        std::string key;
        NSString* str;
        
        buf = gf::PrintAbsyn().print(tree);
        
        key = buf;
        if (deduplicate.find(key) != deduplicate.end()) {
            continue;
        }
        deduplicate.insert(key);
        
        str = [NSString stringWithUTF8String:buf];
        free(buf);
        
        [ret addObject:str];
        
        delete tree;
    }
    
    return ret;
}

- (NSArray*) translationsForLanguage:(NSString*)language {
    gf::PGF* pgf;
    gf::reader::Concrete* concrete;
    gf::Linearizer* linearizer;
    std::vector<gf::Tree*> trees;
    NSMutableArray* ret;
    std::set<std::string> deduplicate;
    
    try {
        pgf = getGrammar();
        if (pgf == NULL) {
            return nil;
        }
        
        concrete = pgf->getConcrete([language UTF8String]);
        if (concrete == NULL) {
            return nil;
        }
    } catch (gf::Exception& e) {
        return nil;
    }
    
    pgf->addReference();
    concrete->addReference();
    try {
        linearizer = new gf::Linearizer(pgf, concrete);
    } catch (gf::Exception& e) {
        gf::release(pgf);
        gf::release(concrete);
        return nil;
    }
    
    
    try {
        trees = state->getTrees();
    } catch (gf::Exception& e) {
        gf::release(linearizer);
        return nil;
    }
        
        
    ret = [[NSMutableArray alloc] init];
    
    for (std::vector<gf::Tree*>::iterator it = trees.begin(); it != trees.end(); it++) {
        gf::Tree* tree = *it;
        char* buf;
        std::string key;
        std::string translation;
        NSString* str;
        
        
        buf = gf::PrintAbsyn().print(tree);
        key = buf;
        free(buf);
        
        if (deduplicate.find(key) != deduplicate.end()) {
            continue;
        }
        deduplicate.insert(key);
        
        
        try {
            translation = linearizer->linearizeString(tree);
            
            str = [NSString stringWithUTF8String:translation.c_str()];
        
            [ret addObject:str];
        } catch (gf::Exception& e) {
            [ret addObject:[NSString stringWithUTF8String:e.getMessage().c_str()]];
        }
        
        delete tree;
    }
    
    gf::release(concrete);
    
    return ret;
}

@end
