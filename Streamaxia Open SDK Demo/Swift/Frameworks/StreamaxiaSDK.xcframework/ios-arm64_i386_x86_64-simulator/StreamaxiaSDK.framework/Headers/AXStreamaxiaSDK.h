//
//  AXStreamaxiaSDK.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 7/15/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

#import "AXSDKDefines.h"

@class AXSDKVersion;
@class AXLicenceInfo;
@class AXError;
@class AXLogSettings;

/**
 Guard for the define of the shortcut to the SDK's singleton.
 */
#ifdef AXStreamaxia
#undef AXStreamaxia
#endif

/**
 This is a shortcut to the SDK singleton.
 */
#define AXStreamaxia [AXStreamaxiaSDK sharedInstance]

/**
 This notification is called after setting up the SDK. Check the sending object, which is the SDK instance for
 success and/or reasons of failure in loading the SDK configuration.
 */
extern NSString * const kAXSDKDidLoadConfigNotification;

/**
 The Streamer SDK. It is the main object for the StreamaxiaSDK and wraps up the initialization and configuration
 of the SDK.
 
 In order to use the Streamer SDK, grab the AXStreamaxiaSDK singleton instance, and then setup the SDK using one 
 of the provided setup methods (default configuration or configuration from a custom URL).
 Make sure that the .config and .key files are either added in the main bundle, or are present as a custom bundle.
 If the latter, then the custom bundle's URL should be used as the custom URL.
 
 The status of the SDK can pe checked using -debugPrintSDKStatus, in order to investigate faulty initizations.
 It also provides info about the expiration date of the licence, the features and the list of valid bundle IDs
 that can be used with the current configuration, if any.
 
 *** SDK Features ***
 The SDK may provide certain features and can be checked if they are available using the -getAvailableFeatures
 method. If a feature is not available, calling the subsequent related APIs will have no effect and will also
 generate some warnings in the console.
 
 *** Trial Versions and Limited time licences ***
 The SDK may be a trial version or it may have a limited time licence. You may check if the licence has expired
 by using the -hasExpired property.
 
 *** Bundle ID lock ***
 The SDK may be configured to work only for certain bundle IDs. You may check if the current bundle ID is valid
 to be used with the SDK by using the -hasValidBundleID property.
 */
@interface AXStreamaxiaSDK : NSObject

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 Returns YES if the SDK is properly configured. This means that the config and the licence key were both valid.
 If this is NO, then make sure that you are using a valid certificate and licence key. Also make sure that the
 certificate and licence key are present at the URL that was used to setup the StreamaxiaSDK.
 
 This property returns NO if the SDK was not yet configured.
 */
@property (nonatomic, assign, readonly) BOOL isConfiguredProperly;

/**
 The licence info. Use this to check if the bundle id is valid, or licence is expired.
 */
@property (nonatomic, strong, readonly) AXLicenceInfo *licence;

/**
 Returns the SDK version.
 */
@property (nonatomic, strong, readonly) AXSDKVersion *version;

/**
 The logging settings.
 */
@property (nonatomic, strong, readonly) AXLogSettings *logSettings;

/// ----------------------------------------
/// @name Lifecycle
/// ----------------------------------------

/**
 The shared instance of this singleton object.
 
 Make sure that the setupSDK or setupSDKWithURL: is called before using the SDK.
 
 @return The initialized object.
 */
+ (instancetype)sharedInstance;

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

/**
 Setups StreamaxiaSDK with the default configuration.
 The configuration and licence key will be searched in the main bundle.
 
 The completion block is called when the SDK has finished loading the configuration. Another option to monitor
 the completion is to listen for the kAXSDKDidLoadConfigNotification notification.
 
 @param completionBlock The completion block.
 */
- (void)setupSDKWithCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/**
 Setups StreamaxiaSDK, with a custom URL.
 The configuration and licence key will be searched at the given URL.
 
 The completion block is called when the SDK has finished loading the configuration. Another option to monitor
 the completion is to listen for the kAXSDKDidLoadConfigNotification notification.
 
 @param url The custom url.
 @param completionBlock The completion block.
 */
- (void)setupSDKWithURL:(NSURL *)url withCompletion:(void (^)(BOOL success, AXError *error))completionBlock;

/**
 Check if a certain feature is provided by the current SDK configuration.
 
 @param feature The SDK feature.
 
 @return YES if the feature is available, NO otherwise.
 */
- (BOOL)providesFeature:(AXSDKFeature)feature;

/**
 Get the available features. The features will be returned as a set of AXSDKFeature (boxed as NSNumber).
 
 @return The set of available features.
 */
- (NSSet<NSNumber *> *)getAvailableFeatures;

/**
 Print the Streamer SDK status. Use this for debug, to see details regarding expiration dates, locked bundles,
 available features. Here will be displayed also if the SDK was successfully loaded.
 */
- (void)debugPrintSDKStatus;

@end
