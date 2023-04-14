//
//  AXRecorderDefines.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 7/15/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;
@import CoreGraphics;

/**
 The audio sample rate presets.

 - AXAudioSampleRate44100Hz: The standard audio sampling rate - 44,1 kHz = 44100 Hz. This is the recommended value to be used.
 */
typedef NS_ENUM(NSInteger, AXAudioSampleRate) {
    AXAudioSampleRate44100Hz = 44100,
    AXAudioSampleRate48000Hz = 48000
};

/**
 Return the audio sample rate as a string.

 @param sampleRate The audio sample rate.

 @return The string value.
 */
extern NSString *AXAudioSampleRateAsString(AXAudioSampleRate sampleRate);

/**
 Preset values for the frame rate, in frames per second.

 - AXFrameRate15fps: 15 fps.
 - AXFrameRate24fps: 24 fps.
 - AXFrameRate30fps: 30 fps.
 - AXFrameRate60fps: 60 fps.
 */
typedef NS_ENUM(NSInteger, AXFrameRate) {
    AXFrameRate15fps = 15,
    AXFrameRate24fps = 24,
    AXFrameRate30fps = 30,
    AXFrameRate60fps = 60,
    AXFrameRate120fps = 120,
    AXFrameRate240fps = 240
};

/**
 Return the frame rate as a string.

 @param frameRate The frame rate.

 @return The string value.
 */
extern NSString *AXFrameRateAsString(AXFrameRate frameRate);

/**
 Video predefined and standard resolutions.

 - AXVideoFrameResolutionCustom:           Use a custom video frame size. Not recommended unless the desired resolution is not available in the presets.
 - AXVideoFrameResolutionStandard144p:     Video frame size class 144p (16:9), having the resolution of 256x144.
 - AXVideoFrameResolutionStandard240p:     Video frame size class 240p (4:3), having the resolution of 320x240.
 - AXVideoFrameResolutionStandardWide240p: Video frame size class 240p - wide (16:9), having the resolution of 426x240.
 - AXVideoFrameResolutionStandard288p:     Video frame size class 288p (4:3), having the resolution of 352x288. This is CIF/SIF standard.
 - AXVideoFrameResolutionStandard360p:     Video frame size class 360p (4:3), having the resolution of 480x360.
 - AXVideoFrameResolutionStandardWide360p: Video frame size class 360p - wide (16:9), having the resolution of 640x360.
 - AXVideoFrameResolutionStandard480p:     Video frame size class 480p (4:3), having the resolution of 640x480.
 - AXVideoFrameResolutionStandardWide480p: Video frame size class 480p - wide (16:9), having the resolution of 854x480.
 - AXVideoFrameResolutionStandard720p:     Video frame size class 720p (16:9), having the resolution of 1280x720 - HD Ready.
 - AXVideoFrameResolutionStandard1080p:    Video frame size class 1080p (16:9), having the resolution of 1920x1080 - Full HD.
 - AXVideoFrameResolutionStandard1440p:    Video frame size class 1440p (16:9), having the resolution of 2560x1440 - Quad HD.
 - AXVideoFrameResolutionStandard2160p:    Video frame size class 2160p, having the resolution of 3840x2160 - 4K (Ultra HD). !!! NOT SUPPORTED YET. !!!
 - AXVideoFrameResolutionStandard4320p:    Video frame size class 4320p, having the resolution of 7680x4320 - 8K. !!! NOT SUPPORTED YET. !!!
 - AXVideoFrameResolutionSize192x144:      Custom video frame size, having the resolution of 192x144. Very low quality video preset.
 - AXVideoFrameResolutionSize960x540:      Custom video frame size, having the resolution of 960x540.
 - AXVideoFrameResolutionSize320x240:      Custom video frame size, having the resolution of 320x240. It's exactly like the 240p class.
 - AXVideoFrameResolutionSize352x288:      Custom video frame size, having the resolution of 352x288. It's exactly like the 288p class.
 - AXVideoFrameResolutionSize640x480:      Custom video frame size, having the resolution of 640x480. It's exactly like the 480p class.
 - AXVideoFrameResolutionSize1280x720:     Custom video frame size, having the resolution of 1280x720. It's exactly like the 720p class.
 - AXVideoFrameResolutionSize1920x1080:    Custom video frame size, having the resolution of 1920x1080. It's exactly like the 1080p class.
 */
typedef NS_ENUM(NSInteger, AXVideoFrameResolution) {
    AXVideoFrameResolutionCustom = 0,
    AXVideoFrameResolutionStandard144p =        192 * 144,
    AXVideoFrameResolutionStandard240p =        320 * 240,
    AXVideoFrameResolutionStandardWide240p =    426 * 240,
    AXVideoFrameResolutionStandard288p =        352 * 288,
    AXVideoFrameResolutionStandard360p =        480 * 360,
    AXVideoFrameResolutionStandardWide360p =    640 * 360,
    AXVideoFrameResolutionStandard480p =        640 * 480,
    AXVideoFrameResolutionStandardWide480p =    854 * 480,
    AXVideoFrameResolutionStandard540p =        960 * 540,
    AXVideoFrameResolutionStandard720p =        1280 * 720,
    AXVideoFrameResolutionStandard1080p =       1920 * 1080,
    AXVideoFrameResolutionStandard1440p =       2560 * 1440,
    AXVideoFrameResolutionStandard2160p =       3840 * 2160,
    AXVideoFrameResolutionStandard4320p =       7680 * 4032,
    AXVideoFrameResolutionSize192x144 =         AXVideoFrameResolutionStandard144p,
    AXVideoFrameResolutionSize320x240 =         AXVideoFrameResolutionStandard240p,
    AXVideoFrameResolutionSize352x288 =         AXVideoFrameResolutionStandard288p,
    AXVideoFrameResolutionSize960x540 =         AXVideoFrameResolutionStandard540p,
    AXVideoFrameResolutionSize640x480 =         AXVideoFrameResolutionStandard480p,
    AXVideoFrameResolutionSize1280x720 =        AXVideoFrameResolutionStandard720p,
    AXVideoFrameResolutionSize1920x1080 =       AXVideoFrameResolutionStandard1080p
};

/**
 Returns an array containing all resolutions.
 
 @return An array containing all resolutions.
 */
extern NSArray<NSNumber *> *AXAllResolutions();

/**
 Returns the video frame resolution as a string.

 @param resolution The resolution.

 @return The string value.
 */
extern NSString *AXVideoFrameResolutionAsString(AXVideoFrameResolution resolution);

/**
 The video orientation.

 - AXVideoOrientationPortrait:  Portrait orientation.
 - AXVideoOrientationLandscape: Landscape orientation.
 - AXVideoOrientationBoth:      Both orientation supported.
 */
typedef NS_ENUM(NSInteger, AXVideoOrientation) {
    AXVideoOrientationPortrait = 0,
    AXVideoOrientationPortraitUpsideDown,
    AXVideoOrientationLandscapeRight,
    AXVideoOrientationLandscapeLeft,
    AXVideoOrientationAutorotate,
};

/**
 Returns the video orientation as a string.

 @param orientation The orientation.

 @return The string value.
 */
extern NSString *AXVideoOrientationAsString(AXVideoOrientation orientation);

/**
 The device cameras.

 - AXCameraBack:  The back camera.
 - AXCameraFront: The front camera.
 */
typedef NS_ENUM(NSInteger, AXCamera) {
    AXCameraBack,
    AXCameraFront
};

/**
 Returns the camera as a string.

 @param camera The camera.

 @return The string value.
 */
extern NSString *AXCameraAsString(AXCamera camera);

/**
 The recording mode.

 - AXRecordingModeAudioAndVideo: The recorder will stream and record both audio and video.
 - AXRecordingModeAudioOnly:     The recorder will stream and record only audio. (This means that the video is not streamed).
 - AXRecordingModeVideoOnly:     The recorder will stream and record only video. (This means that the audio is muted)
 */
typedef NS_ENUM(NSInteger, AXRecordingMode) {
    AXRecordingModeAudioAndVideo = 0,
    AXRecordingModeAudioOnly,
    AXRecordingModeVideoOnly
};

/**
 Returns the recording mode as string.

 @param mode The recording mode.

 @return The string value.
 */
extern NSString *AXRecordingModeAsString(AXRecordingMode mode);

/**
 The torch mode.

 - AXTorchModeOff:  The torch should be off.
 - AXTorchModeOn:   The torch should be on.
 - AXTorchModeAuto: The torch mode is determined automatically by the device, according to the environment.
 */
typedef NS_ENUM(NSInteger, AXTorchMode) {
    AXTorchModeOff = 0,
    AXTorchModeOn,
    AXTorchModeAuto
};

/**
 Returns the torch mode as string.

 @param mode The torch mode.

 @return The string value.
 */
extern NSString *AXTorchModeAsString(AXTorchMode mode);

/**
 The video frame size.
 */
typedef struct {
    /**
     The video frame width, in pixels.
     */
    NSInteger width;
    /**
     The video frame height, in pixels.
     */
    NSInteger height;
} AXVideoFrameSize;

/**
 Makes a video frame size struct with the given width and height.

 @param width  The video frame width.
 @param height The video frame height.

 @return The initialized video frame size struct.
 */
extern AXVideoFrameSize AXVideoFrameSizeMake(NSInteger width, NSInteger height);

/**
 Rotates 90 degrees the given frame size (switches the width and height values).

 @param frameSize The input frame size.

 @return The rotated frame size.
 */
extern AXVideoFrameSize AXVideoFrameSizeRotated(AXVideoFrameSize frameSize);

/**
 Converts the given size to video frame size by rounding the width and height.

 @param size The size.

 @return The video frame size.
 */
extern AXVideoFrameSize AXVideoFrameSizeWithCGSize(CGSize size);

/**
 Converts the given video frame size to CGSize.

 @param frameSize The video frame size.

 @return The size value.
 */
extern CGSize CGSizeWithAXVideoFrameSize(AXVideoFrameSize frameSize);

@interface AXRecorderDefines : NSObject

@end
