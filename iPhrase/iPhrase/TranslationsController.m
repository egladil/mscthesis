//
//  TranslationsController.m
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-20.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import "TranslationsController.h"
#import "TranslationDetailsController.h"

@implementation TranslationsController
{
    NSArray* translations;
    NSArray* disambiguations;
    NSArray* trees;
}

@synthesize grammarian;
@synthesize language;
@synthesize disambiguationLanguage;

- (id)initWithStyle:(UITableViewStyle)style {
    self = [super initWithStyle:style];
    return self;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)viewDidUnload {
    [super viewDidUnload];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    translations = [grammarian translationsForLanguage:language];
    disambiguations = disambiguationLanguage != nil ? [grammarian translationsForLanguage:disambiguationLanguage] : nil;
    trees = [grammarian parseTrees];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.destinationViewController isKindOfClass:[TranslationDetailsController class]]) {
        TranslationDetailsController* translation = (TranslationDetailsController*) segue.destinationViewController;
        UITableViewCell* cell = (UITableViewCell*) sender;
        
        translation.translation = [translations objectAtIndex:cell.tag];
        translation.disambiguation = disambiguations != nil ? [disambiguations objectAtIndex:cell.tag] : nil;
    }
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [translations count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"TranslationCell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
    cell.textLabel.text = [translations objectAtIndex:indexPath.row];
    
    if (disambiguations != nil) {
        cell.detailTextLabel.text = [disambiguations objectAtIndex:indexPath.row];
    } else {
        cell.detailTextLabel.text = [trees objectAtIndex:indexPath.row];
    }
    
    cell.tag = indexPath.row;
    
    return cell;
}
#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
}

- (IBAction)doneTouched:(id)sender {
    [[self navigationController] popViewControllerAnimated:YES];
}

@end
