//
//  AXWarning.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/15/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

#import "AXSDKWarningCodes.h"

/**
 The SDK warning.
 */
@interface AXWarning : NSObject

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 The list of warning codes, wrapped as numbers.
 */
@property (nonatomic, strong, readonly) NSArray<NSNumber *> *warningCodes;

/**
 The warning message.
 */
@property (nonatomic, strong, readonly) NSString *message;

/**
 The list of warnings, as a readable string.
 */
@property (nonatomic, strong, readonly) NSString *warnings;

/// ----------------------------------------
/// @name Lifecycle
/// ----------------------------------------

/**
 Factory method for creating a warning object with a list of warnings and a message.

 @param warningCodes The warning codes, wrapped as numbers.
 @param message      The warning message.

 @return The initialized object.
 */
+ (instancetype)warningWithCodes:(NSArray<NSNumber *> *)warningCodes message:(NSString *)message;

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

/**
 Determines if the current warning contains a certain warning code.

 @param warningCode The warning code.

 @return YES if the warning code is present, NO otherwise.
 */
- (BOOL)containsWarningCode:(AXWarningCode)warningCode;

@end
