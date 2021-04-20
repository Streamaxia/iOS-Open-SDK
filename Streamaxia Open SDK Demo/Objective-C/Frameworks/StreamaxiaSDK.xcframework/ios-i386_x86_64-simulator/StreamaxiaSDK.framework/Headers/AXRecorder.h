//
//  AXRecorder.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 7/15/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;
@import UIKit;
@import AVFoundation;

#import "AXSDKDefines.h"
#import "AXReachability.h"

@class AXRecorderSettings;
@class AXStreamInfo;
@class AXInfo, AXWarning, AXError;

/**
 The recorder state.

 - AXRecorderStateUnknown:             The recording state is unknown.
 - AXRecorderStateStopped:             The streaming is stopped.
 - AXRecorderStateRecording:           The streaming is active.
 - AXRecorderStateStarting:            The streaming is starting.
 - AXRecorderStateStopping:            The streaming is stopping.
 - AXRecorderStateCollectingExtraData: The recorder collects extra data.
 - AXRecorderStateProcessingExtraData: The recorder is processing the extra data.
 */
typedef NS_ENUM(NSInteger, AXRecorderState) {
    AXRecorderStateUnknown = -1,
    AXRecorderStateStopped = 0,
    AXRecorderStateRecording,
    AXRecorderStateStarting,
    AXRecorderStateStopping,
    AXRecorderStateCollectingExtraData,
    AXRecorderStateProcessingExtraData
};

@protocol AXRecorderDelegate;

/**
 The recorder class.
 */
@interface AXRecorder : NSObject

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 The recorder delegate.
 */
@property (nonatomic, weak, readwrite) id<AXRecorderDelegate> recorderDelegate;

/**
 The recorder settings.
 */
@property (nonatomic, strong, readonly) AXRecorderSettings *settings;

/**
 The stream info.
 */
@property (nonatomic, strong, readonly) AXStreamInfo *info;

/**
 The current recorder state.
 */
@property (nonatomic, assign, readonly) AXRecorderState state;

/**
 Returns YES if the recorder is active and is currently recording and/or streaming.
 */
@property (nonatomic, assign, readonly) BOOL isActive;

/**
 Returns YES if the recorder has started capture, NO otherwise.
 */
@property (nonatomic, assign, readonly) BOOL isRecording;

/**
 Returns YES if the recorder is streaming, NO otherwise.
 */
@property (nonatomic, assign, readonly) BOOL isStreaming;

/**
 Returns YES if the recorder has internet access, NO otherwise.
 */
@property (nonatomic, assign, readonly) BOOL hasInternetConnection;

/**
 Returns YES if the recorder has access to the microphone, NO otherwise.
 */
@property (nonatomic, assign, readonly) BOOL hasMicrophoneAccess;

/**
 Returns YES if the recorder has access to the camera, NO otherwise.
 */
@property (nonatomic, assign, readonly) BOOL hasCameraAccess;

/**
 Returns the current streaming bitrate
 */
@property (nonatomic, assign, readonly) NSUInteger currentBitrate;

/// ----------------------------------------
/// @name Lifecycle
/// ----------------------------------------

/**
 Factory method for creating a recorder object, with a stream info and recorder settings.

 @param info     The stream info.
 @param settings The recorder settings.

 @return The initialized object.
 */
+ (instancetype)recorderWithStreamInfo:(AXStreamInfo *)info settings:(AXRecorderSettings *)settings;

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

/**
 Setup the recorder with a custom view, in which the capture output will be displayed.
 This should be called before prepareToRecord. However, it is not mandatory to have an output view.

 @param view The view.

 @return The initialized object.
 */
- (instancetype)setupWithView:(UIView *)view;

/**
 Prepare to record. This must be called before startStreaming.
 
 The capture is also started, and if the recorder has an output view, the capture output will be 
 visible in the view.
 */
- (void)prepareToRecord;

/**
Starts the recording.
The completion block is returning the info about the success of this operation. If recording couldn't be
started, then the error contains info about the reason of failure.

@param completionBlock The completion block.
*/
- (void)startRecordingWithCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/**
Stops the recording.
The completion block is returning the info about the success of this operation. If recording couldn't be
stopped, then the error contains info about the reason of failure.

@param completionBlock The completion block.
*/
- (void)stopRecordingWithCompletion:(void (^)(BOOL success, AXError *error, NSURL *file))completionBlock;

/**
 Starts the streaming.
 The completion block is returning the info about the success of this operation. If streaming couldn't be
 started, then the error contains info about the reason of failure.

 @param completionBlock The completion block.
 */
- (void)startStreamingWithCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/**
 Takes a snapshot of the next available video feed. This method supports just one snapshot simultaneously. Calling this method multiple times without waiting for a response is an error and results in undefined befaviour.
 
 @param completionBlock The completion block.
 */
- (void)takeSnapshotWithCompletion:(void (^)(UIImage *snapshot, AXError *error))completionBlock;

/**
 Stops the streaming.
 */
- (void)stopStreaming;

/**
 Call this method to end the capture session. Make sure to ALWAYS call this method before releasing the Record object
 */
- (void)endSession;

@end

/**
 The recorder delegate. It provides delegate methods for state changes, infos, warnings, errors,
 network status and others.
 */
@protocol AXRecorderDelegate <NSObject>

@optional

/**
 It's called when the recorder state has changed. Implement this to react to the recorder state
 changes and display useful UI.

 @param recorder The recorder.
 @param state    The new state of the recorder.
 */
- (void)recorder:(AXRecorder *)recorder didChangeState:(AXRecorderState)state;

/**
 It's called when the recorder updates the passes time since the start of the streaming.
 The time passed is provided in seconds, since the start of the streaming.

 @param recorder  The recorder.
 @param deltaTime The total time passed.
 */
- (void)recorder:(AXRecorder *)recorder didUpdateStreamTime:(NSTimeInterval)deltaTime;

/**
 It's called when the recorder updates the passes time since the start of the recording.
 The time passed is provided in seconds, since the start of the recording.

 @param recorder  The recorder.
 @param deltaTime The total time passed since recording.
 */
- (void)recorder:(AXRecorder *)recorder didUpdateRecordTime:(NSTimeInterval)deltaTime;

/**
 It's called when the recorder has received some info.

 @param recorder The recorder.
 @param info     The info.
 */
- (void)recorder:(AXRecorder *)recorder didReceiveInfo:(AXInfo *)info;

/**
 It's called when the recorder has received some warnings. 
 
 The warning should be monitored since they may point out incorrect settings, incorrect setups 
 and others that may affect the correct functionality of the recorder.

 @param recorder The recorder.
 @param warning  The warning.
 */
- (void)recorder:(AXRecorder *)recorder didReceiveWarning:(AXWarning *)warning;

/**
 It's called when the recorder has received some errors. 
 
 Usually these are received when something went wrong during the streaming, invalid settings change 
 or other misc errors have been encountered and that will cause the malfunction of the recorder.

 @param recorder The recorder.
 @param error    The error.
 */
- (void)recorder:(AXRecorder *)recorder didReceiveError:(AXError *)error;

/**
 It's called when the network status has changed.

 @param recorder The recorder.
 @param status   The new network status.
 */
- (void)recorder:(AXRecorder *)recorder didChangeNetworkStatus:(AXNetworkStatus)status;

/**
 It's called when a sample buffer was output from the recorder.

 @param recorder The recorder
 @param sampleBuffer The sample buffer
 @param captureOutput The capture output
 */
- (void)recorder:(AXRecorder *)recorder didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromCaptureOutput:(AVCaptureOutput *)captureOutput;

/**
 It's called when an audio buffer was output

 @param recorder The recorder
 @param sampleBuffer The sample buffer
 */
- (void)recorder:(AXRecorder *)recorder didOutputAudioBuffer:(NSData *)data;

/**
 Called after sending a rtmp packet.
 
 @param recorder  The recorder.
 @param bitrate         Previous second bitrate.
 */
- (void)recorder:(AXRecorder *)recorder didUpdateBitrate:(NSUInteger)bitrate;

@end
