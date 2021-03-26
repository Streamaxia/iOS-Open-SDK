//
//  AXRecorderSettings.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 7/15/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;
@import UIKit;

#import "AXRecorderDefines.h"

@interface AXRecorderSettings : NSObject <NSSecureCoding>

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 *  The recording mode. The recorder may record only audio, only video or both video and audio.
 *  For audio recording, access to the deveice's microphone is needed.
 *  For audio recording, access to the deveice's camera is needed.
 *  The default value is AXRecordingModeAudioAndVideo.
 */
@property (nonatomic, assign, readwrite) AXRecordingMode recordingMode;

/**
 *  Returns YES if the recording mode also includes audio.
 */
@property (nonatomic, assign, readonly) BOOL isRecordingAudio;

/**
 *  Returns YES if the recording mode also includes video.
 */
@property (nonatomic, assign, readonly) BOOL isRecordingVideo;

/**
 *  The torch setting while filming.
 *  The default value is AXTorchModeOff.
 */
@property (nonatomic, assign, readwrite) AXTorchMode torchMode;

/**
 *  The current video orientation. The default value is AXVideoOrientationAutorotate.
 */
@property (nonatomic, assign, readwrite) AXVideoOrientation videoOrientation;

/**
 *  The current facing camera.
 *  The default value is AXCameraBack.
 */
@property (nonatomic, assign, readwrite) AXCamera currentCamera;

/**
 *  The frames pe second to be used while streaming and recording video.
 *  The default value is 30fps.
 */
@property (nonatomic, assign, readwrite) NSInteger frameRate;

/**
 *  The keyframe interval used for streaming.
 *  The default value is 30 frames.
 */
@property (nonatomic, assign, readwrite) NSInteger keyFrameInterval;

/**
 *  The audio sample rate.
 *  The default and recommended value is 44100 Hz.
 */
@property (nonatomic, assign, readwrite) NSInteger audioSampleRate;

/**
 *  The video bit rate (in bits per second).
 *  The default value is based on the videoFrameSize property.
 */
@property (nonatomic, assign, readwrite) NSInteger videoBitrate;

/**
 *  The video frame resolution. It is recommended to use the standard predefined resolutions and not the custom one.
 *  The default value is selected based on the screen size.
 */
@property (nonatomic, assign, readwrite) AXVideoFrameResolution videoFrameResolution;

/**
 *  Flag indicating if the resolution width and height should be swapped. The default value is YES.
 *  This causes the streaming to be vertical by default. Set this property to NO to prevent that.
 */
@property (nonatomic, assign, readwrite) BOOL videoFrameResolutionInverted;

/**
 *  The video frame size, in pixels.
 *  The value is determined by the videoFrameResolution value. If AXVideoFrameResolutionCustom is used, this must be set explicitly.
 */
@property (nonatomic, assign, readonly) AXVideoFrameSize videoFrameSize;

/**
 *  Default is NO. Set to YES if you need to customize the audio session.
 */
@property (nonatomic, assign) BOOL configureAudioSessionManually;

/**
 *  Default is NO. Set to YES if your local recording will be available in Photos app.
 */
@property (nonatomic, assign) BOOL exportLocalVideoToAssetLibrary;

/// ----------------------------------------
/// @name Lifecycle
/// ----------------------------------------

/**
 *  Factory method for creating a default recorder settings object.
 *
 *  @return The initialized object.
 */
+ (instancetype)recorderSettings;

/**
 *  Factory method for creating a recorder settings object, with a desired frame size.
 *
 *  @param frameSize The video frame size.
 *
 *  @return The initialized object.
 */
+ (instancetype)recorderSettingsWithVideoFrameSize:(AXVideoFrameResolution)frameSize;

/**
 *  Factory method for creating a recorder settings object from a previously archived data.
 *
 *  @param data The input archived data.
 *
 *  @return The initialized object.
 */
+ (instancetype)recorderSettingsWithArchivedData:(NSData *)data;

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

/**
 *  Explicitly sets a custom frame size and sets the videoFrameResolution property to AXVideoFrameResolutionCustom.
 *
 *  @param frameSize The custom frame size in pixels.
 */
- (void)useCustomVideoFrameSize:(AXVideoFrameSize)frameSize;

/**
 *  Archive this object as a NSData object.
 *
 *  @return The archived data.
 */
- (NSData *)archivedSettings;

@end
