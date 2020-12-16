//
//  AXInfo.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/15/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

#import "AXSDKInfoCodes.h"

/**
 The SDK info.
 */
@interface AXInfo : NSObject

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 The list of info codes, wrapped as numbers.
 */
@property (nonatomic, strong, readonly) NSArray<NSNumber *> *infoCodes;

/**
 The info message.
 */
@property (nonatomic, strong, readonly) NSString *message;

/**
 The list of infos, as a readable string.
 */
@property (nonatomic, strong, readonly) NSString *infos;

/// ----------------------------------------
/// @name Lifecycle
/// ----------------------------------------

/**
 Factory method for creating an info object with a list of info codes and a message.

 @param infoCodes The info codes, wrapped as numbers.
 @param message   The info message.

 @return The initialized object.
 */
+ (instancetype)infoWithCodes:(NSArray<NSNumber *> *)infoCodes message:(NSString *)message;

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

/**
 Determines if the info contains a certain info code.

 @param infoCode The info code.

 @return YES if the info code is present, NO otherwise.
 */
- (BOOL)containsInfoCode:(AXInfoCode)infoCode;

@end
