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
@property (weak, nonatomic) IBOutlet UIView *vIn;
@property (weak, nonatomic) IBOutlet UIScrollView *svSuggestions;

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation;
@end
