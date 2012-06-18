//
//  FirstViewController.h
//  PhraseIOS
//
//  Created by Emil Djupfeldt on 2012-06-14.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface FirstViewController : UIViewController
- (IBAction)translateInput:(id)sender;
@property (weak, nonatomic) IBOutlet UITextField *txtIn;
@property (weak, nonatomic) IBOutlet UITextView *txtOut;

@end
