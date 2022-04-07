//
//  AXMediaFetcher.h
//  StreamaxiaSDK
//
//  Created by Razvan Chelemen on 17/03/2017.
//  Copyright © 2017 Agilio. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AXMovie, AXError;

/**
 Class used to fetch media from the device's library.
 */
@interface AXMediaFetcher : NSObject

/**
 Class used to fetch media from the device's library. NSAppleMusicUsageDescription key must be set in the Info.plist of the app using this API.
 
 @param completionBlock  The block that will be called upon completion. On success a list of movies is given as a parameter, otherwise an error is set.
 */
- (void)getMediaMoviesWithCompletionBlock:(void(^)(NSArray<AXMovie *> *, AXError *))completionBlock;

@end
