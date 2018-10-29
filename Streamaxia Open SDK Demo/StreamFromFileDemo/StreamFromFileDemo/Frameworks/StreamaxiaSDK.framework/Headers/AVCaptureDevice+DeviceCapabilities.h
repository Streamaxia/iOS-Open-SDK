//
//  AVCaptureDevice+DeviceCapabilities.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/19/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import AVFoundation;

#import "AXRecorderDefines.h"

/**
 Utils for determining the device capabilities.
 */
@interface AVCaptureDevice (DeviceCapabilities)

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 Returns the best AVFrameRateRange that is supported by this device.
 */
@property (nonatomic, strong, readonly) AVFrameRateRange *bestSupportedFrameRateRange;

/**
 Returns the best frame rate range that is supported by this device. The range's 
 location is the min frame rate, and the length is the max frame rate.
 */
@property (nonatomic, assign, readonly) NSRange bestSupportedFrameRateNSRange;

/**
 Returns the list of resolutions that are supported by this device. The resolutions 
 are boxed AXVideoFrameResolution.
 */
@property (nonatomic, strong, readonly) NSArray<NSNumber *> *supportedResolutions;

/**
 Returns the list of video frame sizes that are supported by this device. The frame 
 sizes are boxed values of AXVideoFrameSize.
 */
@property (nonatomic, strong, readonly) NSArray<NSValue *> *supportedVideoFrameSizes;

/**
 Returns the best supported session preset by this device.
 */
@property (nonatomic, strong, readonly) NSString *bestSupportedSessionPreset;

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

/**
 Determines if the given frame rate is supported by this device.

 @param frameRate The frame rate.

 @return YES if the frame rate is supported, NO otherwise.
 */
- (BOOL)isFrameRateSupported:(NSInteger)frameRate;

/**
 Determines if the given video frame size is supported by this device.

 @param frameSize The video frame size.

 @return YES if the frame size is supported, NO otherwise.
 */
- (BOOL)isVideoFrameSizeSupported:(AXVideoFrameSize)frameSize;

/**
 Determines if the given standard resolution is supported by this device.

 @param resolution The resolution.

 @return YES if the resolution is supported, NO otherwise.
 */
- (BOOL)isResolutionSupported:(AXVideoFrameResolution)resolution;

/**
 Configures this device for the highest frame rate.
 This method will set the active format and reset the session preset to Input Priority.
 */
- (void)configureForHighestFrameRate;

@end
