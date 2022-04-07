//
//  AXLicenceInfo.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/14/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

/**
 The licence info. Stores useful information about the SDK licence.
 */
@interface AXLicenceInfo : NSObject

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 Returns YES if the SDK has a list of locked bundle IDs, and the current bundle ID is in the list.
 If the SDK is not locked to work only on certain bundle IDs, this property returns YES always.
 */
@property (nonatomic, assign, readonly) BOOL hasValidBundleID;

/**
 Returns YES if the licence for the SDK expired, NO otherwise.
 */
@property (nonatomic, assign, readonly) BOOL hasExpired;

/**
 Returns YES if the licence was loaded.
 */
@property (nonatomic, assign, readonly) BOOL didLoadLicence;

/// ----------------------------------------
/// @name Lifecycle
/// ----------------------------------------

/**
 Factory method for creating a licence info object.
 
 @return The initialized object.
 */
+ (instancetype)licenceInfo;

@end
