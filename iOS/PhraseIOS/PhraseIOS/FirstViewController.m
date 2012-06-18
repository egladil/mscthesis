//
//  FirstViewController.m
//  PhraseIOS
//
//  Created by Emil Djupfeldt on 2012-06-14.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import "FirstViewController.h"
#include <stdio.h>
#include <gu/mem.h>
#include <gu/exn.h>
#include <gu/file.h>
#include <pgf/pgf.h>

#define GRAMMAR "Mountaineering"

static GuPool* gupool = NULL;
static GuExn* guexception = NULL;
static PgfPGF* grammar = NULL;

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
    NSString *grammarPath;
    const char* cGrammarPath;
    FILE* file;
    GuIn* inStream;
    
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    if (gupool == NULL) {
        gupool = gu_new_pool();
    }
    
    if (guexception == NULL) {
        guexception = gu_new_exn(NULL, NULL, gupool);
    }
    
    if (grammar == NULL) {
        grammarPath = [[NSBundle mainBundle] pathForResource:@GRAMMAR ofType:@"pgf"];
        assert(grammarPath != nil);
        
        cGrammarPath = [grammarPath fileSystemRepresentation];
        file = fopen(cGrammarPath, "rb");
        assert(file != NULL);
        
        inStream = gu_file_in(file, gupool);
        
        grammar = pgf_read(inStream, gupool, guexception);
        if (!gu_ok(guexception)) {
            gu_exn_clear(guexception);
            grammar = NULL;
            fclose(file);
            txtOut.text = @"Error loading grammar.";
            return;
        }
        
        // TODO: Free gu input stream?        
        fclose(file);
    }
}

- (void)viewDidUnload
{
    [self setTxtIn:nil];
    [self setTxtOut:nil];
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

- (IBAction)translateInput:(id)sender {
    NSString* text = txtIn.text;
    
    txtOut.text = text;
}

- (BOOL)textFieldShouldReturn:(UITextField *)theTextField {
    if (theTextField == self.txtIn) {
        [theTextField resignFirstResponder];
    }
    return YES;
}
@end
