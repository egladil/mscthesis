//
//  SettingsController.h
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-19.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LanguageSelectionController.h"

@protocol SettingsControllerDelegate <NSObject>
- (void) settingsDone;
- (void) changedFromLanguage:(NSString*) language;
- (void) changedToLanguage:(NSString*) language;

@end

@interface SettingsController : UITableViewController <LanguageSelectionControllerDelegate>
@property (nonatomic, weak) id <SettingsControllerDelegate> delegate;
@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (nonatomic, copy) NSString* fromLanguage;
@property (nonatomic, copy) NSString* toLanguage;
- (IBAction)doneTouched:(id)sender;

@end
