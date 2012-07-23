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
#import "TranslationsController.h"

@implementation MainViewController
{
    Grammarian* grammarian;
    TokenInput* tokenInput;
    AlternativesInput* altInput;
    NSString* newSourceLanguage;
    NSString* targetLanguage;
}


@synthesize vMain = _vMain;
@synthesize vIn = _vIn;
@synthesize svSuggestions = _svSuggestions;
@synthesize btnTranslate;



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
    NSArray* languages;
    
    [super viewDidLoad];
    
    
    grammarian = [[Grammarian alloc] init];
    
    
    languages = [Grammarian languages];
    targetLanguage = nil;
    
    for (NSString* language in languages) {
        if ([[language substringToIndex:6] compare:@"Disamb"] != NSOrderedSame) {
            targetLanguage = language;
            break;
        }
    }
            
    if (targetLanguage == nil && [languages count] > 0) {
        targetLanguage = [languages objectAtIndex:0];
    }
            
    
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
    [self setBtnTranslate:nil];
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
        settings.toLanguage = targetLanguage;
        newSourceLanguage = nil;
    } else if ([segue.destinationViewController isKindOfClass:[TranslationsController class]]) {
        TranslationsController* translations = (TranslationsController*) segue.destinationViewController;
        NSString* disambSource;
        NSString* disambEnglish;
        
        translations.grammarian = grammarian;
        translations.language = targetLanguage;
        
        disambSource = [@"Disamb" stringByAppendingString:[grammarian sourceLanguage]];
        disambEnglish = [@"Disamb" stringByAppendingString:[Grammarian languageForCode:@"Eng"]];
        if ([Grammarian hasLanguage:disambSource]) {
            translations.disambiguationLanguage = disambSource;
        } else if ([Grammarian hasLanguage:disambEnglish]) {
            translations.disambiguationLanguage = disambEnglish;
        } else {
            translations.disambiguationLanguage = nil;
        }
    }
}

- (void) settingsDone {
    if (newSourceLanguage != nil) {
        Grammarian* newGrammarian;
        
        newGrammarian = [[Grammarian alloc] initWithLanguage:newSourceLanguage];
        if (newGrammarian != nil) {
            grammarian = newGrammarian;
            [tokenInput clearTokens];
            [tokenInput setText:@""];
            [self updateSuggestions:[grammarian predict:@""]];
        }
        newSourceLanguage = nil;
    }
}

- (void) changedFromLanguage:(NSString*) language {
    newSourceLanguage = language;
}

- (void) changedToLanguage:(NSString*) language {
    targetLanguage = language;
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
        btnTranslate.enabled = [[grammarian parseTrees] count] > 0;
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
    
    btnTranslate.enabled = [[grammarian parseTrees] count] > 0;
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
