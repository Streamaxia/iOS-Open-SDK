//
//  AXStreamer.h
//  StreamaxiaSDK
//
//  Created by Razvan Chelemen on 01/03/2017.
//  Copyright © 2017 Agilio. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

#import "AXStreamerSettings.h"
#import "AXStreamerVideoSettings.h"
#import "AXStreamerAudioSettings.h"
#import "AXStreamInfo.h"
#import "AXStreamSource.h"
#import "AXWarning.h"

/**
 Errors returned by the AXH264Encoder.
 
 - AXStreamerStateStopped:    The streamer is stopped.
 - AXStreamerStateStarting:   Start stream was called and the streamer is in the starting phase.
 - AXStreamerStateStreaming:  The streamer was successfully started and it streams (the streamer might stream even if there is not stream source).
 - AXStreamerStateStopping:   Stop stream was called and the streamer is stopping.
 */
typedef NS_ENUM(NSInteger, AXStreamerState) {
    AXStreamerStateStopped = 0,
    AXStreamerStateStarting,
    AXStreamerStateStreaming,
    AXStreamerStateStopping
};

@class AXStreamer;

/**
 The streamer delegate receives callbacks when the state of the streamer changes or when an error is encountered.
 */
@protocol AXStreamerDelegate <NSObject>

/**
 Called when the state of the recorder changes.
 
 @param streamer  The streamer.
 @param state     The new state.
 */
- (void)streamer:(AXStreamer *)streamer didChangeState:(AXStreamerState)state;

/**
 Called when a warning is issued.
 
 @param streamer  The streamer.
 @param warning   The warning that was issued.
 */
- (void)streamer:(AXStreamer *)streamer didReceiveWarning:(AXWarning *)warning;

/**
 Called when an error is issued.
 
 @param streamer  The streamer.
 @param error     The error that was issued.
 */
- (void)streamer:(AXStreamer *)streamer didReceiveError:(AXError *)error;

@end

/**
 AXStreamer class can be used to stream from an external source as opposed to AXRecorder which is bound to the device's cameras. It has an internal state that can be controlled using start/stop methods. When the streamer is started it can receive the stream feed through calls to the methods
     - (void)sendVideoBuffer:(CMSampleBufferRef)sampleBuffer;
     - (void)sendAudioBuffer:(CMSampleBufferRef)sampleBuffer;
 It uses a push model and the caller of this methods is responsible for regulating the speed of the feed to realtime, otherwise the buffers might fill and packets will be dropped. It currently accepts raw PCM for audio and raw uncompressed frames for video. Recommanded formats are platform specific YpCbCr8 or RGB.
 */
@interface AXStreamer : NSObject

/**
 The streamer delegate.
 */
@property (nonatomic, weak) id<AXStreamerDelegate>              delegate;

/**
 Streaming settings.
 */
@property (nonatomic, strong, readonly) AXStreamerSettings      *settings;

/**
 Video settings.
 */
@property (nonatomic, strong, readonly) AXStreamerVideoSettings *videoSettings;

/**
 Audio settings.
 */
@property (nonatomic, strong, readonly) AXStreamerAudioSettings *audioSettings;

/**
 The current state of the streamer.
 */
@property (nonatomic, assign, readonly) AXStreamerState         currentState;

/**
 Start the streamer. After calling this method and invoking the block given as a parameter with success, it is safe to start feeding samples to the streamer.
 
 @param completionBlock Block that will be called upon completion.
 */
- (void)startStreamingWithCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/**
 Stop the streaming and release the resources. After calling this method is unsafe to feed samples to the streamer.
 */
- (void)stopStreaming;

/**
 Feed raw video buffer to the streamer. The sample buffer must contain a uncompressed frame and have valid time info.
 */
- (void)sendVideoBuffer:(CMSampleBufferRef)sampleBuffer;

/**
 Feed raw audio buffer to the streamer. The sample buffer must contain maximum 1024 PCM audio samples and have valid time info. Bigger sample buffers might not be handled well by the streamer.
 */
- (void)sendAudioBuffer:(CMSampleBufferRef)sampleBuffer;

/**
Feed raw audio buffer to the streamer. The sample buffer must contain maximum PCM audio samples. Make sure sample rate is same as the value set in the configuration. This method is mutually excluse with - (void)sendAudioBuffer:(CMSampleBufferRef)sampleBuffer; use one or the other.
*/
- (void)sendAudioData:(nullable NSData*)audioData timestamp:(uint64_t)timestamp;

/**
 Add a streaming source. Sources can be added at any point, before and after streaming. By default the newly added stream source is not enabled, meaning that it doesn't stream yet. Setting the on property to YES will establish a connection and start the streaming to that source.
 
 @param streamInfo Stream info used to create the stream source.
 */
- (AXStreamSource *)addStreamSourceWithInfo:(AXStreamInfo *)streamInfo;

/**
 Remove a streaming source. The streaming source won't be managed by the streamer anymore and the streaming will be stopped.
 
 @param streamSource Stream source to be removed.
 */
- (void)removeStreamSource:(AXStreamSource *)streamSource;

@end
