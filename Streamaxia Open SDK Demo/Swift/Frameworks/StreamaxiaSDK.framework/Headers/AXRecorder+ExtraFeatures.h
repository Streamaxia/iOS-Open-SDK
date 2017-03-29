//
//  AXRecorder+ExtraFeatures.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/17/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

#import "AXRecorder.h"
#import "AXStreamSource.h"

/**
 The extra features category.
 */
@interface AXRecorder (ExtraFeatures)

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

/**
Starts the adaptive bitrate service. If a constant bit rates were set they are ignored while adaptive bitrate is started.

@param error Error object is set with an error code and a message if somethings goes wrong with the activation.
*/
- (void)activateFeatureAdaptiveBitRateWithError:(AXError **)error;

/**
 Stops the adaptive bitrate service.
 */
- (void)deactivateFeatureAdaptiveBitRate;

/**
 Activate the save locally feature. To be able to use this feature you must add photos privacy key in your Info.plist:
 <key>NSPhotoLibraryUsageDescription</key>
 <string>Some message.</string>
 The save locally feature can be activated only when the player is stopped, otherwise an error is returned. After calling this method when a stream is started it will autmatically be saved. When the stream is stopped it will be shared to the Photos app and camera roll.
 
 @param error Error object is set with an error code and a message if somethings goes wrong with the activation.
 */
- (void)activateFeatureSaveLocallyWithError:(AXError **)error;

/**
 Deactivate the local save feature.
 The save locally feature can be deactivated only when the player is stopped, otherwise an error is returned.
 
 @param error Error object is set with an error code and a message if somethings goes wrong with the activation.
 */
- (void)deactivateFeatureSaveLocallyWithError:(AXError **)error;

@property (nonatomic, readonly) NSArray<AXStreamSource *> *streamSources;

- (AXStreamSource *)addStreamingSourceWithInfo:(AXStreamInfo *)streamInfo;

- (void)removeStreamingSourceWithInfo:(AXStreamSource *)streamSource;

@end
