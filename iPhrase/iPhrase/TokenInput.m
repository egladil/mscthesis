//
//  TokenInput.m
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-11.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import "TokenInput.h"
#import <QuartzCore/QuartzCore.h>

NSString *const TokenInputTextDidBeginEditingNotification = @"TokenInputTextDidBeginEditingNotification";
NSString *const TokenInputTextDidEndEditingNotification = @"TokenInputTextDidEndEditingNotification";
NSString *const TokenInputTextDidChangeNotification = @"TokenInputTextDidChangeNotification";
NSString* const TokenInputTokenAddedNotification = @"TokenInputTokenAddedNotification";
NSString* const TokenInputTokenRemovedNotification = @"TokenInputTokenRemovedNotification";

NSString* const ZeroWidthSpace = @"\u200B";

@implementation TokenInput
{
    NSCharacterSet* punctuation;
    NSCharacterSet* whitespace;
    NSMutableArray* tokens;
    NSMutableArray* buttons;
    UIView* buttonView;
    UITextField* textField;
    bool processingText;
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    
    punctuation = [NSCharacterSet characterSetWithCharactersInString:@",.;:!?"];
    whitespace = [NSCharacterSet whitespaceAndNewlineCharacterSet];
    
    tokens = [[NSMutableArray alloc] init];
    buttons = [[NSMutableArray alloc] init];
    
    buttonView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 50, 20)];
    [self addSubview:buttonView];
    
    textField = [[UITextField alloc] initWithFrame:CGRectMake(50, 0, 50, 20)];
    [textField setBorderStyle:UITextBorderStyleRoundedRect];
    [textField setAutocapitalizationType:UITextAutocapitalizationTypeNone];
    [textField setAutocorrectionType:UITextAutocorrectionTypeNo];
    [textField setText:ZeroWidthSpace];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onTextFieldDidBeginEditing:) name:UITextFieldTextDidBeginEditingNotification object:textField];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onTextFieldDidChange:) name:UITextFieldTextDidChangeNotification object:textField];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onTextFieldDidEndEditing:) name:UITextFieldTextDidEndEditingNotification object:textField];
    [self addSubview:textField];
    
    processingText = false;
    
    [self setNeedsLayout];
    
    return self;
}


- (NSCharacterSet*) whitespace {
    return whitespace;
}

- (void)setWhitespace:(NSCharacterSet*)ws {
    self.whitespace = ws;
}

- (NSCharacterSet*) punctuation {
    return punctuation;
}

- (void)setPunctuation:(NSCharacterSet*)p {
    self.punctuation = p;
}


- (NSArray*)tokens {
    return [NSArray arrayWithArray:tokens];
}

- (NSString*) lastToken {
    return [tokens lastObject];
}

- (UIButton*)createTokenButton:(NSString*)token {
    UIButton* btn;
    CGSize size;
    
    btn = [UIButton buttonWithType:UIButtonTypeCustom];
    [btn setTitle:token forState:UIControlStateNormal];
    
    size = [token sizeWithFont:[[btn titleLabel] font] constrainedToSize:CGSizeMake(100, 20) lineBreakMode:[[btn titleLabel] lineBreakMode]];
    size.width+= 10;
    
    [btn setFrame:CGRectMake(0, 0, size.width, 20)];
    
    [btn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [btn setBackgroundColor:[UIColor whiteColor]];
    
    btn.layer.borderColor = [UIColor blackColor].CGColor;
    btn.layer.borderWidth = 0.5f;
    btn.layer.cornerRadius = size.width < 20 ? size.width / 2 : 10.0f;
    
    return btn;
}

- (void)addToken:(NSString*)token {
    UIButton* btn;
    
    if ([tokens count] > 0) {
        UIButton* prev;
        
        prev = [buttons lastObject];
        [prev setEnabled:false];
        [prev setBackgroundColor:[UIColor lightGrayColor]];
    }
    
    btn = [self createTokenButton:token];
    [btn addTarget:self action:@selector(onTokenTouched:) forControlEvents:UIControlEventTouchUpInside];
    [buttonView addSubview:btn];
     
    
    [tokens addObject:token];
    [buttons addObject:btn];
    
    [self setNeedsLayout];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:TokenInputTokenAddedNotification object:self];
}

- (void)removeLastToken {
    UIButton* btn;
    
    if ([tokens count] == 0) {
        return;
    }
    
    btn = [buttons lastObject];
    [btn removeFromSuperview];
    
    [tokens removeLastObject];
    [buttons removeLastObject];
    
    if ([tokens count] > 0) {
        UIButton* prev;
        
        prev = [buttons lastObject];
        [prev setEnabled:true];
        [prev setBackgroundColor:[UIColor whiteColor]];
    }
    
    
    [self setNeedsLayout];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:TokenInputTokenRemovedNotification object:self];
}

- (void)clearTokens {
    for (UIButton* btn in buttons) {
        [btn removeFromSuperview];
    }

    [tokens removeAllObjects];
    [buttons removeAllObjects];
    
    [self setNeedsLayout];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:TokenInputTokenRemovedNotification object:self];
}


- (NSString*)text {
    NSString* text;
    
    text = [textField text];
    if ([text compare:ZeroWidthSpace] == NSOrderedSame) {
        return @"";
    }
    
    return text;
}

- (void)setTextNoNotify:(NSString*)text {
    bool oldProcessingText;
    
    oldProcessingText = processingText;
    processingText = true;
    
    if ([text length] == 0) {
        [textField setText:ZeroWidthSpace];
    } else {
        [textField setText:text];
    }
    
    processingText = oldProcessingText;
}

- (void)setText:(NSString*)text {
    [self setTextNoNotify:text];
    [[NSNotificationCenter defaultCenter] postNotificationName:TokenInputTextDidChangeNotification object:self];
}


- (void)layoutSubviews {
    float minInputWidth;
    CGSize size;
    float x;
    CGRect rect;
    
    size = [self frame].size;
    
    minInputWidth = size.width / 3;
    if (minInputWidth > 100) {
        minInputWidth = 100;
    }
    
    
    x = 0;
    for (UIButton* btn in buttons) {
        rect = [btn frame];
        
        rect.origin.x = x;
        rect.origin.y = (size.height - rect.size.height) / 2;
        x+= rect.size.width + 5;
        
        [btn setFrame:rect];
    }
    
    
    rect = [buttonView frame];
    
    rect.size.width = x;
    rect.size.height = size.height;
    if (x <= size.width - minInputWidth) {
        rect.origin.x = 0;
    } else {
        rect.origin.x = size.width - minInputWidth - x;
        x = size.width - minInputWidth;
    }
    
    [buttonView setFrame:rect];
    
    
    rect = [textField frame];
    
    rect.size.width = size.width - x;
    rect.size.height = size.height;
    rect.origin.x = x;
    
    [textField setFrame:rect];
}


- (void)editLastToken {
    if ([tokens count] == 0) {
        [self setText:@""];
        return;
    }
    
    [self setTextNoNotify:[tokens lastObject]];
    [self removeLastToken];
    [[NSNotificationCenter defaultCenter] postNotificationName:TokenInputTextDidChangeNotification object:self];
}

- (IBAction)onTokenTouched:(UIButton*)sender {
    [self editLastToken];
}


- (IBAction)onTextFieldDidBeginEditing:(UITextField*)sender {
    [[NSNotificationCenter defaultCenter] postNotificationName:TokenInputTextDidBeginEditingNotification object:self];
}

- (IBAction)onTextFieldDidChange:(UITextField*)sender {
    NSString* text;
    const char* data;
    size_t len;
    
    if (processingText) {
        return;
    }
    
    text = [textField text];
    
    if ([text length] == 0 || [text compare:ZeroWidthSpace] == NSOrderedSame) {
        [self editLastToken];
        return;
    } 
    
    if ([text length] == 2) {
        if ([[text substringToIndex:1] compare:ZeroWidthSpace] == NSOrderedSame) {
            text = [text substringFromIndex:1];
            [self setTextNoNotify:text];
        } else if ([[text substringFromIndex:1] compare:ZeroWidthSpace] == NSOrderedSame) {
            text = [text substringToIndex:1];
            [self setTextNoNotify:text];
        }   
    }
    
    
    data = [text UTF8String];
    len = strlen(data);
    
    if ([text length] > 0) {
        unichar last;
        bool endsWithWhitespace;
        bool endsWithPunctuation;

        last = [text characterAtIndex:[text length] - 1];
        endsWithWhitespace = [whitespace characterIsMember: last];
        endsWithPunctuation = [punctuation characterIsMember: last];
        
        if (endsWithWhitespace || endsWithPunctuation) {
            NSString* token;
            
            token = [text substringToIndex:[text length] - 1];
            
            [self setTextNoNotify:@""];
            
            if ([token length] > 0) {
                [self addToken:token];
            }
            
            if (endsWithPunctuation) {
                token = [text substringFromIndex:[text length] - 1];
                [self addToken:token];
            }
        }
    }
    
    [[NSNotificationCenter defaultCenter] postNotificationName:TokenInputTextDidChangeNotification object:self];
}

- (IBAction)onTextFieldDidEndEditing:(UITextField*)sender {
    [[NSNotificationCenter defaultCenter] postNotificationName:TokenInputTextDidEndEditingNotification object:self];
}

@end
