//
//  StreamaxiaSDK.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 7/9/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import UIKit;

/*****************************************
 * Version info
 *****************************************/

//! Project version number for StreamaxiaSDK.
FOUNDATION_EXPORT double StreamaxiaSDKVersionNumber;

//! Project version string for StreamaxiaSDK.
FOUNDATION_EXPORT const unsigned char StreamaxiaSDKVersionString[];

/*****************************************
 * SDK Defines
 *****************************************/

#import <StreamaxiaSDK/AXSDKDefines.h>
#import <StreamaxiaSDK/AXRecorderDefines.h>
#import <StreamaxiaSDK/AXFeatureDefines.h>

#import <StreamaxiaSDK/AXSDKInfoCodes.h>
#import <StreamaxiaSDK/AXSDKWarningCodes.h>
#import <StreamaxiaSDK/AXSDKErrorCodes.h>

/*****************************************
 * SDK's Main Interface
 *****************************************/

#import <StreamaxiaSDK/AXStreamaxiaSDK.h>

/*****************************************
 * SDK's Debug Interface
 *****************************************/

#import <StreamaxiaSDK/AXDebug.h>

/*****************************************
 * The Recorder
 *****************************************/

#import <StreamaxiaSDK/AXStreamInfo.h>
#import <StreamaxiaSDK/AXStreamSource.h>

#import <StreamaxiaSDK/AXRecorderSettings.h>

#import <StreamaxiaSDK/AXRecorder.h>
#import <StreamaxiaSDK/AXRecorder+StreamInfo.h>
#import <StreamaxiaSDK/AXRecorder+RecorderSettings.h>
#import <StreamaxiaSDK/AXRecorder+AdvancedSetup.h>
#import <StreamaxiaSDK/AXRecorder+ExtraFeatures.h>

/*****************************************
 * The Streamer
 *****************************************/

#import <StreamaxiaSDK/AXStreamer.h>
#import <StreamaxiaSDK/AXStreamerSettings.h>
#import <StreamaxiaSDK/AXStreamerVideoSettings.h>
#import <StreamaxiaSDK/AXStreamerAudioSettings.h>

#import <StreamaxiaSDK/AXFileInputSource.h>
#import <StreamaxiaSDK/AXMediaFetcher.h>
#import <StreamaxiaSDK/AXMovie.h>

/*****************************************
 * SDK Utils
 *****************************************/

#import <StreamaxiaSDK/AXSDKVersion.h>
#import <StreamaxiaSDK/AXLicenceInfo.h>

#import <StreamaxiaSDK/AXReachability.h>

#import <StreamaxiaSDK/AXInfo.h>
#import <StreamaxiaSDK/AXWarning.h>
#import <StreamaxiaSDK/AXError.h>

#import <StreamaxiaSDK/AXUtils.h>
#import <StreamaxiaSDK/AXUtils+Bitrate.h>
#import <StreamaxiaSDK/AXUtils+Resolution.h>
#import <StreamaxiaSDK/AXUtils+VideoOrientation.h>
#import <StreamaxiaSDK/AXUtils+CaptureDeviceAuthorization.h>

/*****************************************
 * Additions
 *****************************************/

#import <StreamaxiaSDK/AVCaptureDevice+DeviceCapabilities.h>

/*****************************************
 * Logging
 *****************************************/

#import <StreamaxiaSDK/AXLogSettings.h>

/*****************************************
 *****************************************/
