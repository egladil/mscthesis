//
//  FirstViewController.m
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-07.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import "AlternativesInput.h"
#import "FirstViewController.h"
#import "grammar.h"

#include <gf/stringutil.h>
#include <gf/Parser.h>
#include <gf/trees/Printer.H>

static gf::Parser* parser = NULL;

static std::set<std::string> predictCache;
static std::vector<std::string> tokenCache;
static gf::parser::ParseState* psCache = NULL;
static bool errorCache = false;

static std::set<std::string> predict(const std::string& current) {
    std::vector<std::string> tokens;
    bool restart;
    std::string last;
    std::set<std::string> ret;
    
    tokens = gf::split(current, ' ');
    
    restart = false;
    if (psCache == NULL || errorCache || tokens.size() < tokenCache.size()) {
        restart = true;
    } else {
        for (int i = 0; i < tokenCache.size(); i++) {
            if (tokens.at(i) != tokenCache.at(i)) {
                restart = true;
                break;
            }
        }
    }
    
    if (restart) {
        gf::release(psCache);
        try {
            psCache = parser->parse();
        } catch (gf::Exception& e) {
            gf::release(psCache);
            errorCache = true;
            ret.insert("Error creating parser state: " + e.toString());
            return ret;
        }
        tokenCache.clear();
    }
    
    if (restart || current.empty() || current.at(current.size() - 1) == ' ') {
        for (std::vector<std::string>::const_iterator it = tokens.begin() + tokenCache.size(); it != tokens.end(); it++) {
            try {
                if (!psCache->scan(*it)) {
                    break;
                }
            } catch (gf::Exception& e) {
                errorCache = true;
                ret.insert("Error scanning: " + e.toString());
                return ret;
            }
            
            tokenCache.push_back(*it);
        }
        
        if (tokenCache.size() < tokens.size() - 1) {
            errorCache = true;
            ret.insert("Parse error on token: " + tokens.at(tokenCache.size()));
            return ret;
        }
        
        try {
            predictCache = psCache->predict();
        } catch (gf::Exception& e) {
            errorCache = true;
            ret.insert("Error predicting: " + e.toString());
            return ret;
        }
    }
    
    last = tokenCache.size() < tokens.size() ? tokens.back() : "";
    for (std::set<std::string>::const_iterator it = predictCache.begin(); it != predictCache.end(); it++) {
        std::string word = *it;
        
        if (last.empty() || word.substr(0, last.size()) == last) {
            ret.insert(word);
        }
    }
    
    errorCache = false;
    
    return ret;
}

static std::string trees(const std::string& current) {
    gf::parser::ParseState* ps = NULL;
    std::vector<gf::Tree*> trees;
    std::string ret;
    
    try {
        ps = parser->parse(current);
        trees = ps->getTrees();
    } catch (gf::Exception& e) {
        gf::release(ps);
        return "Error predicting: " + e.toString();
    }
    gf::release(ps);
    
    for (std::vector<gf::Tree*>::const_iterator it = trees.begin(); it != trees.end(); it++) {
        ret+= (it == trees.begin() ? "" : "\n");
        ret+= gf::PrintAbsyn().print(*it);
    }
    
    for (std::vector<gf::Tree*>::iterator it = trees.begin(); it != trees.end(); it++) {
        delete *it;
    }
    
    return ret;
}

static NSArray* arrayFromSet(const std::set<std::string>& set) {
    NSMutableArray* array;
    
    array = [NSMutableArray arrayWithCapacity:0];
    
    for (std::set<std::string>::const_iterator it = set.begin(); it != set.end(); it++) {
        [array addObject:[NSString stringWithUTF8String:it->c_str()]];
    }
    
    return [NSArray arrayWithArray:array];
}

static NSArray* arrayFromVector(const std::vector<std::string>& vec) {
    NSMutableArray* array;
    
    array = [NSMutableArray arrayWithCapacity:0];
    
    for (std::vector<std::string>::const_iterator it = vec.begin(); it != vec.end(); it++) {
        [array addObject:[NSString stringWithUTF8String:it->c_str()]];
    }
    
    return [NSArray arrayWithArray:array];
}

@implementation FirstViewController
@synthesize vMain;
@synthesize txtIn;
@synthesize svSuggestions;

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
    gf::PGF* pgf = NULL;
    
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    [txtIn setText:[NSString stringWithUTF8String:""]];
    
    pgf = getGrammar();
    pgf->addReference();
    
    try {
        parser = new gf::Parser(pgf, "MountaineeringEng");
    } catch (gf::Exception& e) {
        gf::release(pgf);
        fprintf(stderr, "Error creating parser: %s\n", e.toString().c_str());
        return;
    }
    
    altInput = [[AlternativesInput alloc] initWithFrame:CGRectMake(5, 0, 290, 100)];
    [altInput setAutoresizingMask:UIViewAutoresizingFlexibleWidth];
    [altInput addTarget:self action:@selector(onAlternative:)];
    [svSuggestions addSubview:altInput];
    
    [txtIn setAutoresizingMask:UIViewAutoresizingFlexibleWidth];
    [svSuggestions setAutoresizingMask:UIViewAutoresizingFlexibleWidth];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardDidShow:) name:UIKeyboardDidShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
    
    [self updateSuggestions:arrayFromSet(predict(""))];
}

- (void)viewDidUnload
{
    [self setTxtIn:nil];
    [self setSvSuggestions:nil];
    [self setVMain:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
    
    gf::release(psCache);
    gf::release(parser);

    altInput = nil;
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

- (void)dealloc {
    /*
    [txtIn release];
    [txtOut release];
    [super dealloc];
    */
}

- (IBAction)inputChanged:(id)sender {
    std::string input;
    
    input = [[txtIn text] UTF8String];
    
    [self updateSuggestions:arrayFromSet(predict(input))];
}

- (IBAction)inputDone:(id)sender {
    std::string input;
    std::string output;
    
    input = [[txtIn text] UTF8String];
    
    output = trees(input);
    
//    [txtOut setText:[NSString stringWithUTF8String:output.c_str()]];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return NO;
}

- (IBAction)onAlternative:(NSString*)word {
    fprintf(stderr, "suggestion %s\n", [word UTF8String]);
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
