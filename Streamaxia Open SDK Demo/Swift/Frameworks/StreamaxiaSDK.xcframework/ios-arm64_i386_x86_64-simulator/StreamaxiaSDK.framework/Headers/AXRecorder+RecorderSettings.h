//
//  AXRecorder+RecorderSettings.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/17/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

#import "AXRecorder.h"
#import "AXRecorderDefines.h"

@class AXError;

@interface AXRecorder (RecorderSettings)

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

/**
 Change and apply the recorder settings.
 This is not allowed while streaming.

 @param settings        The recorder settings.
 @param completionBlock The completion block.
 */
- (void)changeRecorderSettings:(AXRecorderSettings *)settings withCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/// ----------------------------------------
/// @name Recording mode
/// ----------------------------------------

/**
 Check if the current recording mode is fully supported. 
 This methods returns NO if at least one of the audio and video is required but the 
 appropriate device has not been authorized to be used by the user.

 @param recordingMode The recording mode.

 @return YES if recording mode is fully supported, NO otherwise.
 */
- (BOOL)isRecordingModeSupported:(AXRecordingMode)recordingMode;

/**
 Changes the recording mode. Use this method to mute/unmute audio or to enable/disable video.
 Recording mode is allowed to be changed while streaming.

 The completion block returns the operation result. If change was not succesfull, the error
 contains the reason of the failure.

 @param recordingMode The recording mode.
 */
- (void)changeRecordingMode:(AXRecordingMode)recordingMode withCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/// ----------------------------------------
/// @name Camera
/// ----------------------------------------

/**
 Checks if the given camera is present on the device.

 @param camera The camera.

 @return YES if camera is present, NO otherwise.
 */
- (BOOL)isCameraPresent:(AXCamera)camera;

/**
 Switch the active camera to the desired camera.
 Active camera is allowed to be changed while streaming.

 The operation may be succesfull or not. It may fail if the current resolution is not
 supported on the desired camera. Also the camera may not be available for other reasons.
 The success flag in the completion block indicates if the switch was done succesfully.
 If the switch operation fails, check the error to see the reason of the failure.

 @param camera          The new camera.
 @param completionBlock The completion block.
 */
- (void)switchToCamera:(AXCamera)camera withCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/// ----------------------------------------
/// @name Torch Mode
/// ----------------------------------------

/**
 Checks if the given torch mode is supported.

 @param torchMode The torch mode.

 @return YES if the given torch mode is supported, NO otherwise.
 */
- (BOOL)isTorchModeSupported:(AXTorchMode)torchMode;

/**
 Enable or disable the torch (flash light).

 @param torchMode The new value.
 */
- (void)changeTorchMode:(AXTorchMode)torchMode withCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/**
 Changes the torch level. Valid values are between 0.0 (off) and 1.0 (full brightness).
 The given value is clamped in the valid interval.

 If an error occured and torch level can't be set, the error info is returned in the
 completion block.

 @param torchLevel      The torch level.
 @param completionBlock The completion block.
 */
- (void)changeTorchLevel:(float)torchLevel withCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/// ----------------------------------------
/// @name Resolution
/// ----------------------------------------

/**
 Determines if the current active camera supports the given frame size.

 @param frameSize The frame size.

 @return YES if the frame size is supported, NO otherwise.
 */
- (BOOL)isFrameSizeSupported:(AXVideoFrameResolution)frameSize;

/**
 Determines if the current active camera supports the given resolution.

 @param resolution The resolution.

 @return YES if the resolution is supported, NO otherwise.
 */
- (BOOL)isResolutionSupported:(AXVideoFrameResolution)resolution;

/**
 Change the resolution of the currently active camera.
 The resolution is not allowed to be changed while streaming.
 
 If an error occured while changing the resolution, check the error for more info.
 
 It is recommended to change only to supported resolutions. An unsupported custom resolution can be 
 set, but the stream video quality may be degraded due to resolution conversion during the encoding 
 and streaming.
 
 *Note*
 When changing the video resolution, if not using the adaptive video bit rate, it is recommended to 
 adjust the video bit rate to the recommended settings for best quality and performance. If the 
 video bitrate is not appropriate for the selected resolution, the video streaming quality may suffer
 significantly.

 @param resolution      The resolution.
 @param completionBlock The completion block.
 */
- (void)changeVideoResolution:(AXVideoFrameResolution)resolution withCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/**
 Change resolution inversion. Set YES for portrait mode streaming, or NO for landscape.
 
 @param inverted The new flag indicating whether the resolution should be inverted.
 */
- (void)changeResolutionInversion:(BOOL)inverted withError:(AXError **)error;

/// ----------------------------------------
/// @name Frame Rate
/// ----------------------------------------

/**
 Checks if the given frame rate is supported by the current device.

 @param frameRate The frame rate.

 @return YES if the frame rate is supported, NO otherwise.
 */
- (BOOL)isFrameRateSupported:(NSInteger)frameRate;

/**
 Change the frame rate (in fps).
 The frame rate is allowed to be changed while streaming.

 If the new frame rate is not supported, the value is clamped into the supported ranges. The
 new frame rate is returned in the completion block.

 @param frameRate The new frame rate.
 @param completionBlock The completion block.
 */
- (void)changeFrameRate:(NSInteger)frameRate withCompletion:(void (^)(NSInteger validFrameRate))completionBlock;

/// ----------------------------------------
/// @name Key Frame Interval
/// ----------------------------------------

/**
 Change the key frame interval for the video codec.
 The key frame interval is not allowed to be changed while streaming.

 @param keyFrameInterval The new key frame interval (in frames).
 */
- (void)changeKeyFrameInterval:(NSInteger)keyFrameInterval withCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/// ----------------------------------------
/// @name Video Bitrate
/// ----------------------------------------

/**
 Changes the video bit rate. The value should be in bits per second (bps).
 The video bitrate is allowed to be changed while streaming.

 @param videoBitRate The new vide bit rate.
 */
- (void)changeVideoBitrate:(NSInteger)videoBitRate withCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/// ----------------------------------------
/// @name Audio Sample Rate
/// ----------------------------------------

/**
 Change the current audio sample rate setting. It is recommended however to use 44100 Hz.
 The audio sample rate is not allowed to be changed while streaming.

 @param audioSampleRate The new audio sample rate.
 */
- (void)changeAudioSampleRate:(NSInteger)audioSampleRate withCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/// ----------------------------------------
/// @name Audio Bitrate
/// ----------------------------------------

/// ----------------------------------------
/// @name Video Orientation
/// ----------------------------------------

/**
 Change the current video orientation.
 
 @param videoOrientation The new video orientation.
 */
- (void)changeVideoOrientation:(AXVideoOrientation)videoOrientation;

/// ----------------------------------------
/// @name Camera zoom
/// ----------------------------------------

/**
 Change the zoom range for the current camera.
*/
- (NSRange)getZoomRange;

/**
 Change the zoom for the current camera.
*/
- (CGFloat)getZoom;

/**
 Set zoom for the current camera.
*/
- (void)setZoom:(CGFloat)zoom error:(AXError **)error;

@end
