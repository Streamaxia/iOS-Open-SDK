//
//  ViewController.m
//  StreamFromFileDemo
//
//  Created by Razvan Chelemen on 29/10/2018.
//  Copyright © 2018 Streamaxia. All rights reserved.
//

#import "ViewController.h"

#import <StreamaxiaSDK/StreamaxiaSDK.h>

#import "StreamFromFileViewController.h"

@interface ViewController ()

@property (weak, nonatomic) IBOutlet UITableView *tableView;

@property (nonatomic, strong) AXMediaFetcher *mediaFetcher;
@property (nonatomic, strong) NSArray<AXMovie *> *movies;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"cell"];
    
    self.mediaFetcher = [AXMediaFetcher new];
    [self.mediaFetcher getMediaMoviesWithCompletionBlock:^(NSArray<AXMovie *> *movies, AXError *error) {
        if (error) {
            return;
        }
        
        dispatch_async(dispatch_get_main_queue(), ^{
            self.movies = movies;
            [self.tableView reloadData];
        });
    }];
}

#pragma mark - UITableViewDatasource methods


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.movies.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell"];
    AXMovie *movie = self.movies[indexPath.row];
    
    cell.textLabel.text = movie.title;
    
    return cell;
}

#pragma mark - UITableViewDelegate methods

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    StreamFromFileViewController *viewController = [[StreamFromFileViewController alloc] initWithNibName:@"StreamFromFileViewController" bundle:[NSBundle mainBundle]];
    viewController.movie = self.movies[indexPath.row];
    
    [self.navigationController pushViewController:viewController animated:YES];
}


@end
