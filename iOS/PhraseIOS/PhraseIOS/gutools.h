//
//  gutools.h
//  PhraseIOS
//
//  Created by Emil Djupfeldt on 2012-06-20.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#include <gu/map.h>
#include <gu/string.h>
#import <Foundation/Foundation.h>

#ifndef GUTOOLS_H
#define GUTOOLS_H

GuString toGuString(NSString* src, GuPool* pool);


NSString* fromGuString(GuString src);

NSString* dumpStrMap(GuStringMap* map);

#endif /* GUTOOLS_H */
