//
//  TokenInput.h
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-11.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface TokenInput : UIView
- (NSCharacterSet*) whitespace;
- (void)setWhitespace:(NSCharacterSet*)whitespace;
- (NSCharacterSet*) punctuation;
- (void)setPunctuation:(NSCharacterSet*)punctuation;

- (NSArray*)tokens;
- (NSString*) lastToken;
- (void)addToken:(NSString*)token;
- (void)removeLastToken;
- (void)clearTokens;
- (void)editLastToken;

- (NSString*)text;
- (void)setText:(NSString*)text;

- (void)layoutSubviews;

@end

extern NSString* const TokenInputTextDidBeginEditingNotification;
extern NSString* const TokenInputTextDidEndEditingNotification;
extern NSString* const TokenInputTextDidChangeNotification;
extern NSString* const TokenInputTokenAddedNotification;
extern NSString* const TokenInputTokenRemovedNotification;
