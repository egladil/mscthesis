//
//  FirstViewController.m
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-07.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import "AlternativesInput.h"
#import "FirstViewController.h"
#import "TokenInput.h"
#import "Grammarian.h"

@implementation FirstViewController
@synthesize vMain;
@synthesize vIn;
@synthesize svSuggestions;

Grammarian* grammarian = nil;
TokenInput* tokenInput = nil;
AlternativesInput* altInput = nil;


- (void)updateSuggestions:(NSArray*)words
{
    CGRect rect;
    
    [altInput clearAlternatives];
    
    for (NSObject* obj in words) {
        NSString* word;
        
        if (![obj isKindOfClass:[NSString class]]) {
            continue;
        }
        
        word = (NSString*) obj;
        
        [altInput addAlternative:word];
    }
    
    rect = altInput.frame;
    rect.size.height = [altInput optimalHeight];
    [altInput setFrame:rect];
    [svSuggestions setContentSize:rect.size];
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    
    grammarian = [[Grammarian alloc] init];
    
    
    tokenInput = [[TokenInput alloc] initWithFrame:CGRectMake(10, 10, 300, 30)];
    [tokenInput setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
    [vIn addSubview:tokenInput];
    
    
    
    altInput = [[AlternativesInput alloc] initWithFrame:CGRectMake(5, 0, 290, 100)];
    [altInput setAutoresizingMask:UIViewAutoresizingFlexibleWidth];
    [altInput addTarget:self action:@selector(onAlternative:)];
    [svSuggestions addSubview:altInput];
    
    
    [vIn setAutoresizingMask:UIViewAutoresizingFlexibleWidth];
    [svSuggestions setAutoresizingMask:UIViewAutoresizingFlexibleWidth];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardDidShow:) name:UIKeyboardDidShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onTextInput:) name:TokenInputTextDidChangeNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onAddToken:) name:TokenInputTokenAddedNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onRemoveToken:) name:TokenInputTokenRemovedNotification object:nil];
    
    
    [self updateSuggestions:[grammarian predict:@""]];
}

- (void)viewDidUnload
{
    [self setVMain:nil];
    [self setVIn:nil];
    [self setSvSuggestions:nil];
    [super viewDidUnload];

    tokenInput = nil;
    altInput = nil;
    grammarian = nil;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}




- (IBAction)onAlternative:(NSString*)word {
    [tokenInput setText:@""];
    [tokenInput addToken:word];
}

- (IBAction)onTextInput:(TokenInput*)sender {
    NSString* text;
    NSArray* predictions;
    
    text = [tokenInput text];
    
    predictions = [grammarian predict:text];
    if ([predictions count] == 0) {
        predictions = [grammarian predict:text withEditDistance:1];
    }
    
    [self updateSuggestions:predictions];
}

- (IBAction)onAddToken:(TokenInput*)sender {
    NSString* token;
    NSArray* predictions;
    
    token = [tokenInput lastToken];
    
    if ([grammarian accept:token]) {
        [self updateSuggestions:[grammarian predict:@""]];
        return;
    }
    
    predictions = [grammarian matchIgnoringCase:token];
    if ([predictions count] != 1) {
        predictions = [grammarian match:token withEditDistance:1];
        if ([predictions count] != 1) {
            [tokenInput editLastToken];
            return;
        }
    }
    
    [tokenInput removeLastToken];
    [tokenInput addToken:[predictions lastObject]];
}

- (IBAction)onRemoveToken:(TokenInput*) sender {
    NSArray* tokens;
    
    tokens = [tokenInput tokens];
    if ([grammarian acceptedTokenCount] == [tokens count]) {
        return;
    }
    
    [grammarian reset];
    
    for (NSString* token in tokens) {
        [grammarian accept:token];
    }
}



- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    CGRect rect;
    
    rect = altInput.frame;
    rect.size.height = [altInput optimalHeight];
    [altInput setFrame:rect];
    [svSuggestions setContentSize:rect.size];
}

- (void)keyboardDidShow:(NSNotification *)notification {
    CGSize kbdSize;
    CGSize scrSize;
    CGRect rect;
    
    kbdSize = [[[notification userInfo] objectForKey:UIKeyboardFrameBeginUserInfoKey] CGRectValue].size;
    scrSize = [UIScreen mainScreen].applicationFrame.size;
    
    if (UIInterfaceOrientationIsLandscape([self interfaceOrientation])) {
        float tmp;
        
        tmp = kbdSize.width;
        kbdSize.width = kbdSize.height;
        kbdSize.height = tmp;
        
        tmp = scrSize.width;
        scrSize.width = scrSize.height;
        scrSize.height = tmp;
    }
    
    rect = svSuggestions.frame;
    rect.size.height = scrSize.height - rect.origin.y - kbdSize.height;
    
    [svSuggestions setFrame:rect];
}

- (void)keyboardWillHide:(NSNotification *)notification {
    CGSize viewSize;
    CGRect rect;
    
    viewSize = vMain.frame.size;
    
    rect = svSuggestions.frame;
    rect.size.height = viewSize.height - rect.origin.y;
    
    [svSuggestions setFrame:rect];
}

@end
