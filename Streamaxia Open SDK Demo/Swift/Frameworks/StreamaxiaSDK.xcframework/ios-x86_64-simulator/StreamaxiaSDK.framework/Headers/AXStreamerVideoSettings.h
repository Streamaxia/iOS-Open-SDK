//
//  AXVideoSettings.h
//  StreamaxiaSDK
//
//  Created by Razvan Chelemen on 03/03/2017.
//  Copyright © 2017 Agilio. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "AXRecorderDefines.h"

@class AXError;

/**
 The streamer video settings.
 */
@interface AXStreamerVideoSettings : NSObject

/**
 Default video settings.
 */
+ (instancetype)defaultSettings;

/**
 Property used to access the resolution setting.
 */
@property (nonatomic, assign, readonly) AXVideoFrameResolution  resolution;

/**
 *  The video frame size, in pixels.
 *  The value is determined by the videoFrameResolution value. If AXVideoFrameResolutionCustom is used, this must be set explicitly.
 */
@property (nonatomic, assign, readonly) AXVideoFrameSize        videoFrameSize;

/**
 Property used to access the resolution inverted setting.
 */
@property (nonatomic, assign, readonly) BOOL                    resolutionInverted;

/**
 Property used to access the sending video setting.
 */
@property (nonatomic, assign, readonly) BOOL                    sendingVideo;

/**
 Property used to access the output bitrate setting.
 */
@property (nonatomic, assign) NSInteger                         outputBitrate;

/**
 Method used to set the resolution for the stream.
 
 @param resolution Resolution of the stream to be set.
 @param error      Output error. It will be set if the setting could not be set.
 */
- (void)setResolution:(AXVideoFrameResolution)resolution withError:(AXError **)error;

/**
 Method used to set the custom resolution for the stream.
 
 @param frameSize Custom resolution to be set.
 @param error      Output error. It will be set if the setting could not be set.
 */
- (void)setVideoFrameSize:(AXVideoFrameSize)frameSize withError:(AXError **)error ;

/**
 Method used to set the resolution inverted for the stream.
 
 @param resolutionInverted Resolution inversion of the stream to be set.
 @param error              Output error. It will be set if the setting could not be set.
 */
- (void)setResolutionInverted:(BOOL)resolutionInverted withError:(AXError **)error;

/**
 Method used to set the sending video for the stream.
 
 @param enabled Boolean indicating if the caller will send video or not.
 @param error   Output error. It will be set if the setting could not be set.
 */
- (void)setSendingVideo:(BOOL)enabled withError:(AXError **)error;

@end
