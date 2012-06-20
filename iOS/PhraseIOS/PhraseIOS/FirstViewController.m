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
#include <pgf/parser.h>
#include <pgf/lexer.h>
#import "gutools.h"

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
        guexception = gu_new_exn(NULL, gu_kind(type), gupool);
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
    GuPool* localPool = gu_local_pool();
    GuExn* err;
    GuString lang;
    PgfConcr* concrete;
    GuString startcatFlag;
    GuString defaultCategory;
    PgfCId* startcat;
    GuReader* input;
    PgfLexer* lexer;
    PgfParseState* state;
    PgfToken token;
    GuEnum* result;
    PgfExprProb* expression;
    GuStringBuf* output;
    
    lang = gu_str_string("MountaineeringEng", localPool);
    
    concrete = gu_map_get(grammar->concretes, &lang, PgfConcr*);
    assert(concrete != NULL);
    
    startcatFlag = gu_str_string("startcat", localPool);
    defaultCategory = gu_str_string("Phrase", localPool);
    
    txtOut.text = dumpStrMap(grammar->gflags);
    
    startcat = gu_map_get(grammar->gflags, &startcatFlag, PgfCId*);
    if (startcat == NULL) {
        startcat = &defaultCategory;
    }    
    
    input = gu_string_reader(convNSStringtoGuString([txtIn.text stringByAppendingString:@" "], localPool), localPool);
    lexer = pgf_new_lexer(input, localPool);
    assert(lexer != NULL);
    
    state = pgf_parser_init_state(concrete, *startcat, 0, localPool);
    assert(state != NULL);
    
    err = gu_new_exn(NULL, gu_kind(type), localPool);
    
    while (true) {
        token = pgf_lexer_next_token(lexer, err, localPool);
        if (!gu_ok(err)) {
            break;
        }
        
        state = pgf_parser_next_state(state, token, localPool);
        if (state == NULL) {
            txtOut.text = @"Unexpected token";
            goto exit;
        }
    }
    
    result = pgf_parse_result(state, localPool);
    
    expression = gu_next(result, PgfExprProb*, localPool);
    if (expression == NULL) {
        txtOut.text = @"No results";
        goto exit;
    }
    
    output = gu_string_buf(localPool);
    err = gu_new_exn(NULL, gu_kind(type), localPool);
    
    pgf_print_expr(expression->expr, 0, gu_string_buf_writer(output), err);
    if (!gu_ok(err)) {
        txtOut.text = @"Could not print";
        goto exit;
    }
    
    txtOut.text = convGuStringToNSString(gu_string_buf_freeze(output, localPool));
    
exit:
    gu_pool_free(localPool);
}

- (BOOL)textFieldShouldReturn:(UITextField *)theTextField {
    if (theTextField == self.txtIn) {
        [theTextField resignFirstResponder];
    }
    return YES;
}
@end
