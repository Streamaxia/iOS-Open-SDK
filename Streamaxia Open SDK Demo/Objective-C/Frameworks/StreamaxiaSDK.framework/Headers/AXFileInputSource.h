//
//  AXFileInputSource.h
//  StreamaxiaSDK
//
//  Created by Razvan Chelemen on 16/03/2017.
//  Copyright © 2017 Agilio. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@class AXFileInputSource, AXError;

/**
 The delegate of the file input source. Returns the samples read from the file.
 */
@protocol AXFileInputSourceDelegate <NSObject>

/**
 Called after a new video sample was read.
 
 @param streamer  The input source.
 @param state     The sample read.
 */
- (void)fileInputSource:(AXFileInputSource *)inputSource didReadVideoSample:(CMSampleBufferRef)sampleBuffer;

/**
 Called after a new audio sample was read.
 
 @param streamer  The input source.
 @param state     The sample read.
 */
- (void)fileInputSource:(AXFileInputSource *)inputSource didReadAudioSample:(CMSampleBufferRef)sampleBuffer;

@end

/**
 This class can be used to stream audio and video from a file. It opens the file at the provided URL and starts reading sample buffers from it at a realtime speed.
 */
@interface AXFileInputSource : NSObject

/**
 The input source delegate.
 */
@property (nonatomic, weak) id<AXFileInputSourceDelegate> delegate;

/**
 The video file URL to be used for streaming. This property must be set before calling - (void)startReadingWithError:(AXError **)error.
 */
@property (nonatomic, strong) NSURL *videoURL;

/**
 Start the streamer. After calling this method and invoking the block given as a parameter with success, it is safe to start feeding samples to the streamer. Calling this method multiple times without calling - (void)stopReading in between is an error.
 
 @param error   Output error. It will be set if the setting could not be set.
 */
- (void)startReadingWithError:(AXError **)error;

/**
 Stop reading from the file.
 */
- (void)stopReading;

@end
