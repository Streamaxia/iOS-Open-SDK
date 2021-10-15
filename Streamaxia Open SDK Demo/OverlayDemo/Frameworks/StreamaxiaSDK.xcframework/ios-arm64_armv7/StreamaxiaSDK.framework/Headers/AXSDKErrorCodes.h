//
//  AXSDKErrorCodes.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/9/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

/**
 The SDK error codes.
 */
typedef NS_ENUM(NSInteger, AXErrorCode) {
    AXErrorCodeUnknown = -1,
    AXErrorCodeGenericError = 0,

    AXErrorCodeNeedsAccessToMicrophone = 1001,
    AXErrorCodeNeedsAccessToCamera,

    AXErrorCodeCameraNotPresent = 2001,
    AXErrorCodeCameraUnavailable,

    AXErrorCodeTorchModeNotSupported = 3001,
    AXErrorCodeTorchModeUnavailable,
    AXErrorCodeTorchLevelUnavailable,

    AXErrorCodeKeyFrameIntervalLocked = 4001,

    AXErrorCodeBitrateCannotChange = 5001,
    AXErrorCodeAudioSampleRateIsLocked,

    AXErrorCodeResolutionIsLocked = 6001,
    AXErrorCodeResolutionNotSupported,
    AXErrorCodeBitrateNotSupported,

    AXErrorCodeCaptureSessionError = 10001,

    AXErrorCodeStreamingError = 11001,
    AXErrorCodeStreamerNotReady,
    AXErrorCodeLostServerConnection,
    AXErrorCodeNoInternetConnection,
    AXErrorCodeStreamingAlreadyRunning,
    
    AXErrorCodeSDKInvalidConfiguration = 20001,
    AXErrorCodeSDKLicenceHasExpired,
    AXErrorCodeSDKInvalidBundleID,
    AXErrorCodeSDKInvalidLicenceKey,
    AXErrorCodeSDKFeatureNotAvailable,
    AXErrorCodeSDKLicenseInvalidOnCurrentVersion,
    
    AXErrorCodeAudioEncodingFailure = 60001,
    AXErrorCodeVideoEncodingFailure = 70001,
    AXErrorCodeRTMPConnectionFailure = 80001,
    AXErrorCodeLocalSaveFailure = 90001,
    AXErrorPostToPhotosFailure = 100001,
    AXErrorPhotosAccessError,
    
    AXErrorMediaLibraryAccessError = 101001,
    
    AXErrorKeychainAccessFailure = 110001,
    AXErrorStreamLimitReached = 120001
};

/**
 Returns the error code as a string.

 @param code The error code.

 @return The string representation.
 */
extern NSString *AXErrorCodeAsString(AXErrorCode code);

@interface AXSDKErrorCodes : NSObject

@end
