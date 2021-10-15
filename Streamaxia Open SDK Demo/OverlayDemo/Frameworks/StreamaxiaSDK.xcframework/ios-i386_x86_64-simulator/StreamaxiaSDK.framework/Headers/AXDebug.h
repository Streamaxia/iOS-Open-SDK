//
//  AXDebug.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/8/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

@class AXRecorderSettings;
@class AXStreamInfo;

/**
 The debug class. Contains several utils for debugging the SDK.
 */
@interface AXDebug : NSObject

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 The imported certificate preview. This contains some useful info and it should be used just for
 debugging purposes.
 */
@property (nonatomic, strong, readonly) NSString *importedCertificatePreview;

/**
 The original (exported) certificate preview. This contains some useful info and it should be used
 just for debugging purposes.
 */
@property (nonatomic, strong, readonly) NSString *originalCertificatePreview;

/// ----------------------------------------
/// @name Lifecycle
/// ----------------------------------------

/**
 Factory method for creating a debug object.

 @return The initialized object.
 */
+ (instancetype)debug;

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

/**
 Returns a debug string representation for the given recorder settings.

 @param settings The recorder settings.

 @return The string representation.
 */
- (NSString *)stringFromRecorderSettings:(AXRecorderSettings *)settings;

/**
 Returns a debug string representation for the given stream info.

 @param streamInfo The stream info.

 @return The string representation.
 */
- (NSString *)stringFromStreamInfo:(AXStreamInfo *)streamInfo;

@end
