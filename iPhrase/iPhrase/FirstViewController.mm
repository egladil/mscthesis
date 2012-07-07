//
//  FirstViewController.m
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-07.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import "FirstViewController.h"
#import "grammar.h"

#include <gf/Parser.h>

gf::Parser* parser = NULL;

static std::string predict(const std::string& current) {
    gf::parser::ParseState* ps = NULL;
    std::set<std::string> predict;
    std::string ret;
    
    try {
        ps = parser->parse(current);
        predict = ps->predict();
    } catch (gf::Exception& e) {
        gf::release(ps);
        return "Error predicting: " + e.toString();
    }
    gf::release(ps);
    
    for (std::set<std::string>::const_iterator it = predict.begin(); it != predict.end(); it++) {
        ret+= (it == predict.begin() ? "" : "\n") + *it;
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
        parser = new gf::Parser(pgf, "FoodsEng");
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
//    [txtOut setText:[NSString stringWithUTF8String:"done"]];
}

@end
