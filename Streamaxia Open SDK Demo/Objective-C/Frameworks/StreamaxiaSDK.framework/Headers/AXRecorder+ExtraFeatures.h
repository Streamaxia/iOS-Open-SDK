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

/**
 Active the tap to focus feature. The activation must be made after the sdk was successfully configured.
 */
- (void)activateFeatureTapToFocusWithCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/**
 Deactivate the tap to focus feature.
 */
- (void)deactivateFeatureTapToFocus;

/**
 List of stream sources that are currently managed by the recorder. A stream source is created internally when the recorder is started. Extra stream sources can be added by calling - (AXStreamSource *)addStreamingSourceWithInfo:(AXStreamInfo *)streamInfo. By default when a stream source is added it does NOT start streaming. To start streaming to that source you must set the on property to YES.
 */
@property (nonatomic, readonly) NSArray<AXStreamSource *> *streamSources;

/**
 Add a new stream source with the given info. Adding a source with an invalid info might result in an invalid stream source. Adding two sources with the same URL is an error and the behaviour is undefined. Stream sources can be added/removed dynamically at any point during streaming.
 
  @param streamInfo The stream info to be used to create the stream source.
  @return The stream source that is now managed by the recorder. You can set the delegate property to receive messages from the source and you can start the streaming on that source by setting the on property to YES.
 */
- (AXStreamSource *)addStreamingSourceWithInfo:(AXStreamInfo *)streamInfo;

/**
 Remove a stream source from the recorder. After calling this method the stream source is not managed by the recorder anymore and it can't be used for streaming.
 
 @param streamSource The stream source to be removed.
 */
- (void)removeStreamingSourceWithInfo:(AXStreamSource *)streamSource;

@end
