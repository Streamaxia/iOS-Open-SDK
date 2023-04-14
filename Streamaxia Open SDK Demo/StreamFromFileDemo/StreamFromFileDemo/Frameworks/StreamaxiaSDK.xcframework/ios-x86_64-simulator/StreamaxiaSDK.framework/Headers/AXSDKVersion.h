//
//  AXSDKVersion.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/9/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

/**
 The version of the SDK. It provides info about the current version of the SDK.
 */
@interface AXSDKVersion : NSObject

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 The SDK's major version.
 */
@property (nonatomic, assign, readonly) NSInteger major;

/**
 The SDK's minor version.
 */
@property (nonatomic, assign, readonly) NSInteger minor;

/**
 The SDK's patch version.
 */
@property (nonatomic, assign, readonly) NSInteger patch;

/**
 The build string.
 */
@property (nonatomic, assign, readonly) NSString *build;

/**
 The short string representation for the current SDK version.
 It looks like this: v<major>.<minor>.<patch>.
 */
@property (nonatomic, strong, readonly) NSString *shortString;

/**
 The long string representation for the current SDK version.
 It looks like this: v<major>.<minor>.<patch> (build <build>).
 */
@property (nonatomic, strong, readonly) NSString *longString;

/// ----------------------------------------
/// @name Lifecycle
/// ----------------------------------------

/**
 Factory method for creating a version object.
 
 @return The initialized object.
 */
+ (instancetype)version;

@end
