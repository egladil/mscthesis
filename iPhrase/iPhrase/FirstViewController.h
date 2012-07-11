//
//  FirstViewController.h
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-07.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface FirstViewController : UIViewController
@property (weak, nonatomic) IBOutlet UIView *vMain;
@property (weak, nonatomic) IBOutlet UITextField *txtIn;
@property (weak, nonatomic) IBOutlet UIView *vIn;
@property (weak, nonatomic) IBOutlet UIScrollView *svSuggestions;

- (IBAction)inputChanged:(id)sender;
- (IBAction)inputDone:(id)sender;
- (BOOL)textFieldShouldReturn:(UITextField *)textField;

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation;
@end
