//
//  SettingsController.m
//  iPhrase
//
//  Created by Emil Djupfeldt on 2012-07-19.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#import "SettingsController.h"
#import "Grammarian.h"

@implementation SettingsController
@synthesize delegate;
@synthesize tableView;
@synthesize fromLanguage;
@synthesize toLanguage;

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (!self) {
        return nil;
    }
    
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];

    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
 
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

- (void)viewDidUnload
{
    [self setTableView:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    switch (section) {
        case 0:
            return 2;
        default:
            return 0;
    }
}

static const int TagFromLanguage = 0;
static const int TagToLanguage = 1;

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"LanguageCell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
    switch (indexPath.row) {
        case 0:
            cell.textLabel.text = @"From";
            cell.detailTextLabel.text = [Grammarian humanReadableNameOfLanguage:fromLanguage];
            cell.tag = TagFromLanguage;
            break;
        case 1:
            cell.textLabel.text = @"To";
            cell.detailTextLabel.text = [Grammarian humanReadableNameOfLanguage:toLanguage];
            cell.tag = TagToLanguage;
            break;
    }
    
    return cell;
}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
}
     
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.destinationViewController isKindOfClass:[LanguageSelectionController class]] &&
        [sender isKindOfClass:[UITableViewCell class]]) {
        LanguageSelectionController* langsel = (LanguageSelectionController*) segue.destinationViewController;
        UITableViewCell* cell = (UITableViewCell*) sender;
        
        langsel.delegate = self;
        
        switch (cell.tag) {
            case TagFromLanguage:
                langsel.setting = @"From";
                langsel.language = fromLanguage;
                break;
            case TagToLanguage:
                langsel.setting = @"To";
                langsel.language = toLanguage;
                break;
        }
    }
}

- (void) languageSelected:(NSString *)language  forSetting:(NSString*) setting {
    if ([@"From" compare:setting] == NSOrderedSame) {
        fromLanguage = language;
        [delegate changedFromLanguage:language];
    } else if ([@"To" compare:setting] == NSOrderedSame) {
        toLanguage = language;
        [delegate changedToLanguage:language];
    }
    
    [tableView reloadData];
}

- (IBAction)doneTouched:(id)sender {
    [[self navigationController] popViewControllerAnimated:YES];
    [delegate settingsDone];
}

@end
