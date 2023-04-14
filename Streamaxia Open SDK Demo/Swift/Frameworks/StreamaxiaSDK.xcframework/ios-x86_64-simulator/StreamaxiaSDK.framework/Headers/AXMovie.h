//
//  AXMovie.h
//  StreamaxiaSDK
//
//  Created by Razvan Chelemen on 17/03/2017.
//  Copyright © 2017 Agilio. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Movie model used to retrieve media from device's library.
 */
@interface AXMovie : NSObject

/**
 The title of the movie.
 */
@property (nonatomic, strong) NSString *title;

/**
 The url of the movie.
 */
@property (nonatomic, strong) NSURL    *url;

@end
