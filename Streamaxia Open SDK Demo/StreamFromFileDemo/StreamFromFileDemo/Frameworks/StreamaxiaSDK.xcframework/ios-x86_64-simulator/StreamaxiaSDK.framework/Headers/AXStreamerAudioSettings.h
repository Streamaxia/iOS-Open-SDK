//
//  AXAudioSettings.h
//  StreamaxiaSDK
//
//  Created by Razvan Chelemen on 03/03/2017.
//  Copyright © 2017 Agilio. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "AXError.h"

/**
 The streamer audio settings.
 */
@interface AXStreamerAudioSettings : NSObject

/**
 Default audio settings.
 */
+ (instancetype)defaultSettings;

/**
 Property used to access the audio output bitrate setting.
 */
@property (nonatomic, assign) NSUInteger outputBitrate;

/**
 Property used to access the send audio setting.
 */
@property (nonatomic, assign, readonly) BOOL sendingAudio;

/**
 Property used to access the audio sample rate setting.
 */
@property (nonatomic, assign, readonly) NSUInteger sampleRate;

/**
 Property used to access the channels number for the stream.
 */
@property (nonatomic, assign, readonly) NSUInteger channelsNumber;

/**
 Method used to set the sample rate for the stream.
 
 @param sampleRate Sample rate of the stream to be set.
 @param error      Output error. It will be set if the setting could not be set.
 */
- (void)setSampleRate:(NSUInteger)sampleRate withError:(AXError **)error;

/**
 Method used to set the channels number for the stream.
 
 @param channelsNumber Channels number to be set.
 @param error          Output error. It will be set if the setting could not be set.
 */
- (void)setChannelsNumber:(NSUInteger)channelsNumber withError:(AXError **)error;

/**
 Method used to set the sending audio for the stream.
 
 @param enabled  Sending audio enabled.
 @param error    Output error. It will be set if the setting could not be set.
 */
- (void)setSendingAudio:(BOOL)enabled withError:(AXError **)error;

@end
