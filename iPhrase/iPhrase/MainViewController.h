//
//  MainViewController.h
//  earg
//
//  Created by Emil Djupfeldt on 2012-07-15.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import "SettingsController.h"

@interface MainViewController : UIViewController <SettingsControllerDelegate>

@property (weak, nonatomic) IBOutlet UIView *vMain;
@property (weak, nonatomic) IBOutlet UIView *vIn;
@property (weak, nonatomic) IBOutlet UIScrollView *svSuggestions;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *btnTranslate;

@end
