//
//  AXSDKDefines.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 8/3/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

/**
 The SDK Features.

 - AXSDKFeatureAdaptiveBitRate:  The adaptive bit rate feature.
 - AXSDKFeatureSaveVideoLocally: The save video locally feature.
 - AXSDKFeatureTapToFocus:       The tap to focus camera feature.
 - AXSDKFeatureFaceSwap:         The face swap feature.
 - AXSDKFeatureBasicFilters:     The basic filters feature.
 - AXSDKFeatureSendPhoto:        The send photo feature.
 */
typedef NS_ENUM(NSInteger, AXSDKFeature) {
    AXSDKFeatureAdaptiveBitRate = 0,
    AXSDKFeatureSaveVideoLocally,
    AXSDKFeatureTapToFocus,
    AXSDKFeatureFaceSwap,
    AXSDKFeatureBasicFilters,
    AXSDKFeatureSendPhoto
};

/**
 Returns the SDK feature as a string.

 @param feature The SDK feature.
 
 @return The string value.
 */
extern NSString *AXSDKFeatureAsString(AXSDKFeature feature);

/**
 Logging
 */

typedef NS_ENUM(NSInteger, AXLogLevel) {
    AXLogLevelInfo = 0,
    AXLogLevelWarning,
    AXLogLevelError,
    AXLogLevelOff
};

typedef NS_ENUM(NSInteger, AXLogOutput) {
    AXLogOutputConsole = 0,
    AXLogOutputFile
};

typedef NS_ENUM(NSInteger, AXLogScope) {
    AXLogScopeAll = 0,
    AXLogScopeRTMP,
    AXLogScopeBuffering,
    AXLogScopeVideoDecoder,
    AXLogScopeAudioDecoder,
};
