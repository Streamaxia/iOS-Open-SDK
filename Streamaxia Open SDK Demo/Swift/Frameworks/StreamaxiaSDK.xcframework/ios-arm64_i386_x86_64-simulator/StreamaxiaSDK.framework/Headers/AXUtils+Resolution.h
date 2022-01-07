//
//  AXUtils+Resolution.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/11/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import UIKit;

#import "AXUtils.h"
#import "AXRecorderDefines.h"

/**
 The video resolution utils.
 */
@interface AXUtils (Resolution)

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 The list of all the resolutions defined in the SDK, as wrapped values.
 */
@property (nonatomic, strong, readonly) NSArray<NSNumber *> *allResolutions;

/**
 The list of resolution and their corresponding frame sizes, as CGSize wrapped values.
 */
@property (nonatomic, strong, readonly) NSDictionary<NSNumber *, NSValue *> *frameSizes;

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

/**
 Provides the frame size for the given video resolution.

 @param resolution The resolution.

 @return The frame size, in pixels.
 */
- (AXVideoFrameSize)frameSizeForResolution:(AXVideoFrameResolution)resolution;

/**
 Provides a string representation for a given resolution.
 
 @param resolution The resolution.
 
 @return A string representation for current resolution.
 */
- (NSString *)stringRepresentationForFrameSize:(AXVideoFrameSize)resolution;

@end
