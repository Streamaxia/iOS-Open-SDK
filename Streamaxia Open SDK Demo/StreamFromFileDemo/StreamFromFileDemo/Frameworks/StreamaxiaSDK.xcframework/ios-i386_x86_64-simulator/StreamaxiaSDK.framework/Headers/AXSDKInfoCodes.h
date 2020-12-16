//
//  AXSDKInfoCodes.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/17/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

/**
 The info codes.
 */
typedef NS_ENUM(NSInteger, AXInfoCode) {
    AXInfoCodeUnknown = -1,
    AXInfoCodeGenericInfo = 0,
    
    AXInfoCodeCaptureSessionDidStartRunning = 1001,
    AXInfoCodeCaptureSessionDidStopRunning,

    AXInfoCodeStreamerIsReady,
    
    AXInfoCodeStreamingLimit = 2001,
    
    AXInfoCodeBitrateChange = 3001,
};

/**
 Returns the info code as a string.

 @param code The info code.

 @return The string representation.
 */
extern NSString *AXInfoCodeAsString(AXInfoCode code);

@interface AXSDKInfoCodes : NSObject

@end
