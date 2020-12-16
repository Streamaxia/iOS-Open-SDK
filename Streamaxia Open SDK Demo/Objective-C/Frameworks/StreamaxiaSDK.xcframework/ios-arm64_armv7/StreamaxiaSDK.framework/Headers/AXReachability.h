//
//  AXReachability.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 7/19/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;
@import SystemConfiguration;

/**
 The notification sent when the network reachability status changes.
 The monitoring must be on in order to be notified of network status changes.
 */
extern NSString * const kAXReachabilityDidChangeNotification;

/**
 The network reachability status values.

 - AXNetworkStatusNotReachable:     The network is not reachable.
 - AXNetworkStatusReachableViaWiFi: The network is reachable on WiFi.
 - AXNetworkStatusReachableViaWWAN: The network is reachable on the cellular network.
 */
typedef NS_ENUM(NSInteger, AXNetworkStatus) {
    AXNetworkStatusNotReachable = 0,
    AXNetworkStatusReachableViaWiFi,
    AXNetworkStatusReachableViaWWAN
};

/**
 The network reachability monitor.
 */
@interface AXReachability : NSObject

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 The block called when the network becomes reachable.
 The monitoring must be on in order to be notified of network status changes.
 */
@property (nonatomic, copy, readwrite) void (^networkDidBecomeReachableBlock)(AXNetworkStatus status);

/**
 The block called when the network becomes unreachable.
 The monitoring must be on in order to be notified of network status changes.
 */
@property (nonatomic, copy, readwrite) void (^networkDidBecomeUnreachableBlock)(void);

/**
 The block called when the network reachability status changes.
 The monitoring must be on in order to be notified of network status changes.
 */
@property (nonatomic, copy, readwrite) void (^networkDidChangeReachabilityBlock)(AXNetworkStatus status);

/**
 Returns YES if a connection is required.
 */
@property (nonatomic, assign, readonly) BOOL isConnectionRequired;

/**
 Rturns YES if the connection required is on-demand (it is not dynamic).
 */
@property (nonatomic, assign, readonly) BOOL isConnectionOnDemand;

/**
 Returns YES if the user intervetion is required to make a connection.
 */
@property (nonatomic, assign, readonly) BOOL isUserInteractionRequired;

/**
 Returns YES if the network is reachable (either on cellular or WiFi).
 */
@property (nonatomic, assign, readonly) BOOL isReachable;

/**
 Returns YES if the network is reachable on the local WiFi.
 */
@property (nonatomic, assign, readonly) BOOL isReachableOnWiFi;

/**
 Returns YES if the network is reachable on the cellular network.
 */
@property (nonatomic, assign, readonly) BOOL isReachableOnWWAN;

/**
 Returns YES if the monitoring of network status was started.
 */
@property (nonatomic, assign, readonly) BOOL didStartMonitoringNetworkStatus;

/**
 The current network reachability status.
 */
@property (nonatomic, assign, readonly) AXNetworkStatus currentReachabilityStatus;

/**
 The current network reachability, as a readable string.
 */
@property (nonatomic, strong, readonly) NSString *currentReachabilityString;

/// ----------------------------------------
/// @name Lifecycle
/// ----------------------------------------

/**
 Factory method for creating a network reachability object, using a host name.

 @param hostName The host name (e.g. www.apple.com).

 @return The initialized object.
 */
+ (instancetype)reachabilityWithHostName:(NSString *)hostName;

/**
 Factory method for creating a network reachability object, using a host address.

 @param hostAddress The host address (a reference to a sockaddr_in variable).

 @return The initialized object.
 */
+ (instancetype)reachabilityWithHostAddress:(void *)hostAddress;

/**
 Factory method for creating a network reachability object for monitoring internet reachability.

 @return The initialized object.
 */
+ (instancetype)reachabilityForInternetConnection;

/**
 Factory method for creating a network reachability object, for monitoring internet reachability on WiFi only.

 @return The initialized object.
 */
+ (instancetype)reachabilityForLocalWiFi;

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

/**
 Start monitoring the network status updates. 
 To be informed about the changes, either subscribe to the notifications (kAXReachabilityDidChangeNotification)
 or use the desired blocks to monitor the changes (networkDidBecomeReachableBlock, networkDidBecomeUnreachableBlock 
 or networkDidChangeReachabilityBlock).

 @return YES if the monitoring was started with success, NO otherwise.
 */
- (BOOL)startMonitoringNetworkStatus;

/**
 Stop monitoring the network status updates.
 */
- (void)stopMonitoringNetworkStatus;

/**
 Get the network flags as a string. Use this for debugging.

 @return The flags string.
 */
- (NSString *)debugFlagsString;

/**
 Get the object description, for debug purposes. 
 Use this for debugging.

 @return The object description.
 */
- (NSString *)debugDescription;

@end
