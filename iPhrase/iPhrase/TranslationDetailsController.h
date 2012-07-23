//
//  TranslationDetailsController.h
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-23.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface TranslationDetailsController : UIViewController
@property (weak, nonatomic) IBOutlet UITextView *textField;

@property (nonatomic, copy) NSString* translation;
@property (nonatomic, copy) NSString* disambiguation;

@end
