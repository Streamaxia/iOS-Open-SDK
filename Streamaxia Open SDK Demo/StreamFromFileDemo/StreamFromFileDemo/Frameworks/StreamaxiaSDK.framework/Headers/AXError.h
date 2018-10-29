//
//  AXError.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/9/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

#import "AXSDKErrorCodes.h"

/**
 The SDK error.
 */
@interface AXError : NSObject

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 The list of error codes, wrapped as numbers.
 */
@property (nonatomic, strong, readonly) NSArray<NSNumber *> *errorCodes;

/**
 The error message.
 */
@property (nonatomic, strong, readonly) NSString *message;

/**
 The list of errors, as a readable string.
 */
@property (nonatomic, strong, readonly) NSString *errors;

/**
 A custom info object that can be attached to the error.
 */
@property (nonatomic, strong, readwrite) id userInfo;

/// ----------------------------------------
/// @name Lifecycle
/// ----------------------------------------

/**
 Factory method for creating an error object with a list of error codes and a message.

 @param errorCodes The error codes, wrapped as numbers.
 @param message    The error message.

 @return The initialized object.
 */
+ (instancetype)errorWithCodes:(NSArray<NSNumber *> *)errorCodes message:(NSString *)message;

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

/**
 Check if this error contains a certain error code.

 @param errorCode The error code.

 @return YES if the error code is present, NO otherwise.
 */
- (BOOL)containsErrorCode:(AXErrorCode)errorCode;

@end
