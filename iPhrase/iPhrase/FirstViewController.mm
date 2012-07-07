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

static std::string predict(const std::string& current) {
    std::vector<std::string> tokens;
    bool restart;
    std::string last;
    std::string ret;
    
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
            return "Error creating parser state: " + e.toString();
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
                return "Error scanning: " + e.toString();
            }
            
            tokenCache.push_back(*it);
        }
        
        if (tokenCache.size() < tokens.size() - 1) {
            errorCache = true;
            return "Parse error on token: " + tokens.at(tokenCache.size());
        }
        
        try {
            predictCache = psCache->predict();
        } catch (gf::Exception& e) {
            errorCache = true;
            return "Error predicting: " + e.toString();
        }
    }
    
    last = tokenCache.size() < tokens.size() ? tokens.back() : "";
    for (std::set<std::string>::const_iterator it = predictCache.begin(); it != predictCache.end(); it++) {
        std::string word = *it;
        
        if (last.empty() || word.substr(0, last.size()) == last) {
            ret+= *it + "\n";
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

@implementation FirstViewController
@synthesize txtIn;
@synthesize txtOut;

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
    
    [txtOut setText:[NSString stringWithUTF8String:predict("").c_str()]];
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
    [txtIn release];
    [txtOut release];
    [super dealloc];
}

- (IBAction)inputChanged:(id)sender {
    std::string input;
    std::string output;
    
    input = [[txtIn text] UTF8String];
    
    output = predict(input);
    
    [txtOut setText:[NSString stringWithUTF8String:output.c_str()]];
}

- (IBAction)inputDone:(id)sender {
    std::string input;
    std::string output;
    
    input = [[txtIn text] UTF8String];
    
    output = trees(input);
    
    [txtOut setText:[NSString stringWithUTF8String:output.c_str()]];
}

@end
