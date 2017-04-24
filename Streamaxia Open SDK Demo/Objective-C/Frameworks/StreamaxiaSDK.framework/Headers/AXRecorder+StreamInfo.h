//
//  AXRecorder+StreamInfo.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/17/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

#import "AXRecorder.h"

@interface AXRecorder (StreamInfo)

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

/**
 Change and apply the stream info. The recorder holds the initial stream source (which is created internally when the recorder is started). When calling this method the old stream source is replaced by a new one.
 This is not allowed while streaming.

 @param streamInfo      The stream info.
 @param completionBlock The completion block.
 */
- (void)changeStreamInfo:(AXStreamInfo *)streamInfo withCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

@end
