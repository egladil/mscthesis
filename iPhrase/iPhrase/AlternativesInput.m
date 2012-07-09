//
//  AlternativesInput.m
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-09.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import "AlternativesInput.h"

@implementation AlternativesInput

NSMutableArray* wordOrder = nil;
NSMutableDictionary* buttonsForWords = nil;
NSMutableDictionary* wordsForButtons = nil;

NSMutableDictionary* targetHelper = nil;
NSMutableDictionary* targets = nil;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self == nil) {
        return nil;
    }
    
    wordOrder = [[NSMutableArray alloc] init];
    buttonsForWords = [[NSMutableDictionary alloc] init];
    wordsForButtons = [[NSMutableDictionary alloc] init];
    
    targetHelper = [[NSMutableDictionary alloc] init];
    targets = [[NSMutableDictionary alloc] init];
    
    return self;
}


- (void)addTarget:(id)target action:(SEL)action {
    NSValue* key;
    NSMutableSet* actions;
    
    key = [NSValue valueWithNonretainedObject:target];
    actions = (NSMutableSet*) [targets objectForKey:key];
    if (actions == nil) {
        actions = [[NSMutableSet alloc] init];
        [targets setObject:actions forKey:key];
        [targetHelper setObject:target forKey:key];
    }
    
    [actions addObject:[NSValue valueWithPointer:action]];
}

- (void)removeTarget:(id)target action:(SEL)action {
    NSValue* key;
    NSMutableSet* actions;
    
    key = [NSValue valueWithNonretainedObject:target];
    actions = (NSMutableSet*) [targets objectForKey:key];
    if (actions == nil) {
        return;
    }

    [actions removeObject:[NSValue valueWithPointer:action]];
    if ([actions count] == 0) {
        [targets removeObjectForKey:key];
        [targetHelper removeObjectForKey:key];
    }
}

- (void)notifyTargets:(NSString*)word {
    [targets enumerateKeysAndObjectsUsingBlock:^(NSValue* key, NSMutableSet* actions, BOOL *stop) {
        id target;
        
        target = [targetHelper objectForKey:key];
        if (target != nil) {
            [actions enumerateObjectsUsingBlock:^(NSValue* action, BOOL *stop) {
                [target  performSelector:[action pointerValue] withObject:word afterDelay:0];
            }];
        }
    }];
}

- (void)addAlternative:(NSString*)word {
    UIButton* btn;
    CGSize size;
    
    if ([buttonsForWords objectForKey:word] != nil) {
        return;
    }
    
    btn = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [btn setTitle:word forState:UIControlStateNormal];
    [btn addTarget:self action:@selector(onAlternativeTouched:) forControlEvents:UIControlEventTouchUpInside];

    size = [word sizeWithFont:[[btn titleLabel] font] constrainedToSize:CGSizeMake(100, 20) lineBreakMode:[[btn titleLabel] lineBreakMode]];
    
    [btn setFrame:CGRectMake(0, 0, size.width + 10, 20)];
    [self addSubview:btn];
    
    [buttonsForWords setObject:btn forKey:word];
    [wordsForButtons setObject:word forKey:[NSValue valueWithNonretainedObject:btn]];
    [wordOrder addObject:word];
    
    [self setNeedsLayout];
}

- (void)removeAlternative:(NSString*)word {
    UIButton* btn;
    
    btn = [buttonsForWords objectForKey:word];
    if (btn == nil) {
        return;
    }

    [btn removeFromSuperview];
    
    [buttonsForWords removeObjectForKey:word];
    [wordsForButtons removeObjectForKey:[NSValue valueWithNonretainedObject:btn]];
    [wordOrder removeObject:word];
    
    [self setNeedsLayout];
}

- (void)clearAlternatives {
    [buttonsForWords enumerateKeysAndObjectsUsingBlock:^(NSString* word, UIButton* btn, BOOL *stop) {
        [btn removeFromSuperview];
    }];
    
    [buttonsForWords removeAllObjects];
    [wordsForButtons removeAllObjects];
    [wordOrder removeAllObjects];
    
    [self setNeedsLayout];
}

- (IBAction)onAlternativeTouched:(UIButton*)sender {
    NSString* word;
    
    word = [wordsForButtons objectForKey:[NSValue valueWithNonretainedObject:sender]];
    if (word == nil) {
        return;
    }
    
    [self notifyTargets:word];
}

- (void)layoutSubviews {
    float x;
    float y;
    CGSize max;
    
    x = 0;
    y = 0;
    max = self.frame.size;
    for (NSString* word in wordOrder) {
        UIButton* btn;
        CGRect rect;
        
        btn = [buttonsForWords objectForKey:word];
        rect = btn.frame;
        
        if (x + rect.size.width > max.width) {
            x = 0;
            y+= rect.size.height + 5;
        }
        
        rect.origin.x = x;
        rect.origin.y = y;
        
        x+= rect.size.width + 5;
        
        [btn setFrame:rect];
    }
}

@end
