//
//  MainViewController.m
//  earg
//
//  Created by Emil Djupfeldt on 2012-07-15.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import "MainViewController.h"
#import "AlternativesInput.h"
#import "Grammarian.h"
#import "TokenInput.h"

@implementation MainViewController
{
    Grammarian* grammarian;
    TokenInput* tokenInput;
    AlternativesInput* altInput;
    NSString* sourceLanguage;
}


@synthesize vMain = _vMain;
@synthesize vIn = _vIn;
@synthesize svSuggestions = _svSuggestions;



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
    rect.size.height = [altInput optimalHeight] + 10;
    [altInput setFrame:rect];
    [_svSuggestions setContentSize:rect.size];
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
    [_vIn addSubview:tokenInput];
    
    
    
    altInput = [[AlternativesInput alloc] initWithFrame:CGRectMake(5, 5, 290, 100)];
    [altInput setAutoresizingMask:UIViewAutoresizingFlexibleWidth];
    [altInput addTarget:self action:@selector(onAlternative:)];
    [_svSuggestions addSubview:altInput];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardDidShow:) name:UIKeyboardDidShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onTextInput:) name:TokenInputTextDidChangeNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onTextEnd:) name:TokenInputTextDidEndEditingNotification object:nil];
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
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
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


- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.destinationViewController isKindOfClass:[SettingsController class]]) {
        SettingsController* settings = (SettingsController*) segue.destinationViewController;
        
        settings.delegate = self;
        settings.fromLanguage = [grammarian sourceLanguage];
        sourceLanguage = nil;
    }
}

- (void) settingsDone {
    if (sourceLanguage != nil) {
        Grammarian* newGrammarian;
        
        newGrammarian = [[Grammarian alloc] initWithLanguage:sourceLanguage];
        if (newGrammarian != nil) {
            grammarian = newGrammarian;
            [tokenInput clearTokens];
            [tokenInput setText:@""];
            [self updateSuggestions:[grammarian predict:@""]];
        }
        sourceLanguage = nil;
    }
}

- (void) changedFromLanguage:(NSString*) language {
    sourceLanguage = language;
}

- (void) changedToLanguage:(NSString*) language {
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

- (IBAction)onTextEnd:(TokenInput*)sender {
    fprintf(stderr, "onTextEnd\n");
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
    rect.size.height = [altInput optimalHeight] + 10;
    [altInput setFrame:rect];
    [_svSuggestions setContentSize:rect.size];
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
    
    rect = _svSuggestions.frame;
    rect.size.height = scrSize.height - rect.origin.y - kbdSize.height;
    
    [_svSuggestions setFrame:rect];
}

- (void)keyboardWillHide:(NSNotification *)notification {
    CGSize viewSize;
    CGRect rect;
    
    viewSize = _vMain.frame.size;
    
    rect = _svSuggestions.frame;
    rect.size.height = viewSize.height - rect.origin.y;
    
    [_svSuggestions setFrame:rect];
}

@end
