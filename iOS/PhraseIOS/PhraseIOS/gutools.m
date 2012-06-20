//
//  gutools.m
//  PhraseIOS
//
//  Created by Emil Djupfeldt on 2012-06-20.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#include <gu/mem.h>
#include <gu/exn.h>
#include <gu/file.h>

#import "gutools.h"


GuString toGuString(NSString* src, GuPool* pool) {
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

NSString* fromGuString(GuString src) {
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

NSString* dumpStrMap(GuStringMap* map) {
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
    
    gu_map_iter(map, &it->it, exn);
    
    if (gu_ok(exn)) {
        ret = fromGuString(gu_string_buf_freeze(sb, localPool));
    }
    
    gu_pool_free(localPool);
    return ret;
}
