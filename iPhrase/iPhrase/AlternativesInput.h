//
//  AlternativesInput.h
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-09.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AlternativesInput : UIView
- (void)addTarget:(id)target action:(SEL)action;
- (void)removeTarget:(id)target action:(SEL)action;

- (void)addAlternative:(NSString*)word;
- (void)removeAlternative:(NSString*)word;
- (void)clearAlternatives;

- (void)layoutSubviews;
@end
