//
//  TranslationsController.h
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-20.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Grammarian.h"

@interface TranslationsController : UITableViewController
@property (nonatomic, weak) Grammarian* grammarian;
@property (nonatomic, copy) NSString* language;

- (IBAction)doneTouched:(id)sender;
@end
