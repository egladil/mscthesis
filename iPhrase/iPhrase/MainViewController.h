//
//  MainViewController.h
//  earg
//
//  Created by Emil Djupfeldt on 2012-07-15.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import "FlipsideViewController.h"

@interface MainViewController : UIViewController <FlipsideViewControllerDelegate, UIPopoverControllerDelegate>

@property (strong, nonatomic) UIPopoverController *flipsidePopoverController;
@property (weak, nonatomic) IBOutlet UIView *vMain;
@property (weak, nonatomic) IBOutlet UIView *vIn;
@property (weak, nonatomic) IBOutlet UIScrollView *svSuggestions;

@end
