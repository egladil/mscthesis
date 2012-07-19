//
//  LanguageSelectionController.h
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-19.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol LanguageSelectionControllerDelegate <NSObject>
- (void) languageSelected:(NSString*) language forSetting:(NSString*) setting;
@end

@interface LanguageSelectionController : UITableViewController
@property (nonatomic, weak) id <LanguageSelectionControllerDelegate> delegate;
@property (nonatomic, copy) NSString* setting;
@property (nonatomic, copy) NSString* language;
@end
