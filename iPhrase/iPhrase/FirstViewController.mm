//
//  FirstViewController.m
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-07.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

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
@synthesize txtIn;
@synthesize txtOut;

NSMutableArray* suggestions = nil;


- (void)updateSuggestions:(NSArray*)words
{
    float y = 0;
    
    for (UIButton* btn in suggestions) {
        [btn removeFromSuperview];
//        [btn release];
    }
    
    [suggestions removeAllObjects];
    
    for (NSObject* obj in words) {
        NSString* word;
        UIButton* btn;
        
        if (![obj isKindOfClass:[NSString class]]) {
            continue;
        }
        
        word = (NSString*) obj;
        
        btn = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        [btn setTitle:word forState:UIControlStateNormal];
        [btn setFrame:CGRectMake(10, y+= 30, 100, 20)];
        [btn addTarget:self action:@selector(onSuggestionTouched:) forControlEvents:UIControlEventTouchUpInside];

        [suggestions addObject:btn];
        [txtOut addSubview:btn];
    }
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
    [txtOut setText:[NSString stringWithUTF8String:""]];
    
    pgf = getGrammar();
    pgf->addReference();
    
    try {
        parser = new gf::Parser(pgf, "MountaineeringEng");
    } catch (gf::Exception& e) {
        gf::release(pgf);
        fprintf(stderr, "Error creating parser: %s\n", e.toString().c_str());
        return;
    }
    
    suggestions = [NSMutableArray arrayWithCapacity:0];
    
    [self updateSuggestions:arrayFromSet(predict(""))];
}

- (void)viewDidUnload
{
    [self setTxtIn:nil];
    [self setTxtOut:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
    
    gf::release(psCache);
    gf::release(parser);

    suggestions = nil;
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
    
    [txtOut setText:[NSString stringWithUTF8String:output.c_str()]];
}

- (IBAction)onSuggestionTouched:(id)sender {
    UIButton* btn;
    
    if (![sender isKindOfClass:[UIButton class]]) {
        return;
    }
    
    btn = (UIButton*) sender;
    
    fprintf(stderr, "suggestion %s\n", [[btn titleForState:UIControlStateNormal] UTF8String]);
}

@end
