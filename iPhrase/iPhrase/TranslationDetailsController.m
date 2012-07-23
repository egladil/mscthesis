//
//  TranslationDetailsController.m
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-23.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import "TranslationDetailsController.h"
#import <QuartzCore/QuartzCore.h>

@implementation TranslationDetailsController
@synthesize textField;
@synthesize translation;
@synthesize disambiguation;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (!self) {
        return nil;
    }
    
    return self;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
}

#pragma mark - View lifecycle


- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    textField.text = disambiguation == nil ? translation : [[translation stringByAppendingString:@"\n\n"] stringByAppendingString:disambiguation];
}

- (void)viewDidUnload {
    [self setTextField:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

@end
