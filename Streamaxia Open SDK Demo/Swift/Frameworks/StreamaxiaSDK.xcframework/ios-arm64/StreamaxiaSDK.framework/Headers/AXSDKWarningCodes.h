//
//  AXSDKWarningCodes.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/17/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

/**
 The warning codes.
 */
typedef NS_ENUM(NSInteger, AXWarningCode) {
    AXWarningCodeUnknown = -1,
    AXWarningCodeGenericWarning = 0,
};

/**
 Returns the warning code as a string.

 @param code The warning code.

 @return The string representation.
 */
extern NSString *AXWarningCodeAsString(AXWarningCode code);

@interface AXSDKWarningCodes : NSObject

@end
