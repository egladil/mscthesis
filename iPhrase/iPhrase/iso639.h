//
//  iso639.h
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-15.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef iPhrase_iso639_h
#define iPhrase_iso639_h

struct info_t {
    const char* iso639_2;
    const char* iso639_1;
    const char* name;
};

#ifdef __cplusplus
extern "C" {
#endif
    
void generateLanguageInfoCache();
struct info_t* getLanguageInfo(const char* iso639_2);
    
#ifdef __cplusplus
}
#endif

#endif
