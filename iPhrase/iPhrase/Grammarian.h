//
//  Grammarian.h
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-11.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Grammarian : NSObject
- (id)init;
- (id)initWithLanguage:(NSString*)language;

+ (NSArray*)languages;
+ (NSString*) codeForLanguage:(NSString*)language;
+ (NSString*) languageForCode:(NSString*)code;

- (NSArray*)predict:(NSString*)prefix;
- (NSArray*)predict:(NSString*)prefix withEditDistance:(int)distance;
- (NSArray*)match:(NSString*)token withEditDistance:(int)distance;
- (NSArray*)matchIgnoringCase:(NSString*)token;

- (BOOL)accept:(NSString*)token;
- (void)reset;
- (int) acceptedTokenCount;

- (NSArray*) parseTrees;
@end
