//
//  FirstViewController.h
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-07.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface FirstViewController : UIViewController
@property (retain, nonatomic) IBOutlet UITextField *txtIn;
@property (retain, nonatomic) IBOutlet UITextView *txtOut;

- (IBAction)inputChanged:(id)sender;
- (IBAction)inputDone:(id)sender;
@end
