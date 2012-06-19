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

static GuString toGuString(NSString* src, GuPool* pool) {
    size_t length;
    char* data;
    
    length = [src lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    data = gu_malloc(pool, length + 1);
    
    memcpy(data, [src UTF8String], length);
    data[length] = 0;
    
    return gu_str_string(data, pool);
}

typedef struct StringOut {
    GuOutStream stream;
    GuPool* pool;
    char* buf;
    size_t size;
    size_t pos;
} StringOut;

static size_t strOutHelper(GuOutStream* stream, const uint8_t* buf, size_t len, GuExn* err) {
	StringOut* strout = gu_container(stream, StringOut, stream);
    size_t newPos;
    
    newPos = strout->pos + len;
    
    if (buf == NULL || newPos > strout->size) {
        size_t newSize;
        char* tmp;
        
        newSize = strout->size + 1024;
        newSize = newSize < newPos ? newPos + 1024 : newSize;
        
        tmp = gu_malloc(strout->pool, newSize);
        assert(tmp != NULL);
        
        memcpy(tmp, strout->buf, strout->size);
        strout->buf = tmp;
        strout->size = newSize;
    }
    
    memcpy(strout->buf, buf, len);
    strout->pos = newPos;
    
    return len;
}

static NSString* fromGuString(GuString src) {
    GuPool* localPool = gu_local_pool();
    StringOut* strout;
    GuWriter* writer;
    GuExn* exn;
    NSString* ret = nil;
    
    strout = gu_new_s(localPool, StringOut, .stream.output = strOutHelper, .pool = localPool);
    writer = gu_new_utf8_writer(gu_new_out(&strout->stream, localPool), localPool);
    
    exn = gu_new_exn(NULL, gu_kind(type), localPool);
    
    gu_string_write(src, writer, exn);
    
    if (gu_ok(exn)) {
        ret = [NSString stringWithUTF8String:(strout->buf != NULL ? strout->buf : "")];
    }
     
    gu_pool_free(localPool);
    return ret;
}


typedef struct DumpStrMapIter {
    GuMapItor it;
    GuWriter* writer;
} DumpStrMapIter;

static void dumpStrMapHelper(GuMapItor* self, const void* key, void* value, GuExn *err) {
	DumpStrMapIter* dumper = gu_container(self, DumpStrMapIter, it);
    GuString* str = (GuString*) key;
    
    gu_string_write(*str, dumper->writer, err);
}

static NSString* dumpStrMap(GuStringMap* map) {
    GuPool* localPool = gu_local_pool();
    GuExn* exn;
    GuStringBuf* sb;
    GuWriter* writer;
    DumpStrMapIter* it;
    NSString* ret;
    
    sb = gu_string_buf(localPool);
    writer = gu_string_buf_writer(sb);
    
    it = gu_new_s(localPool, DumpStrMapIter, .it.fn = dumpStrMapHelper, .writer = writer);
    exn = gu_new_exn(NULL, gu_kind(type), localPool);
    
    gu_map_iter(grammar->gflags, &it->it, exn);
    
    if (gu_ok(exn)) {
        ret = fromGuString(gu_string_buf_freeze(sb, localPool));
    }
    
    gu_pool_free(localPool);
    return ret;
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
    
    txtOut.text = fromGuString(*startcat);
    
    
    input = gu_string_reader(toGuString([txtIn.text stringByAppendingString:@" "], localPool), localPool);
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
    
    txtOut.text = fromGuString(gu_string_buf_freeze(output, localPool));
    
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
