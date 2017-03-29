//
//  AXStreamInfo.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 7/15/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;

/**
 *  The model wrapping the stream info. It is mandatory to set the server address,
 *  the application name and the stream name.
 */
@interface AXStreamInfo : NSObject <NSSecureCoding>

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 *  The server address (e.g. 20.237.227.201).
 *  This must be mandatory set.
 */
@property (nonatomic, strong, readwrite) NSString *serverAddress;

/**
 *  The application name.
 *  This must be mandatory set.
 */
@property (nonatomic, strong, readwrite) NSString *applicationName;

/**
 *  The stream name.
 *  This must be mandatory set.
 */
@property (nonatomic, strong, readwrite) NSString *streamName;

/**
 *  If set to YES, will use RTMPS protocol, otherwise will use RTMP. 
 *  The default value is NO.
 */
@property (nonatomic, assign, readwrite) BOOL useSecureConnection;

/**
 *  The user name for the streaming server. Defaults to empty string.
 */
@property (nonatomic, strong, readwrite) NSString *username;

/**
 *  The password for the streaming server. Defaults to empty string.
 */
@property (nonatomic, strong, readwrite) NSString *password;

/**
 *  The full stream URL.
 */
@property (nonatomic, strong, readonly) NSURL *streamURL;

/**
 *  The full stream URL string. 
 *  It is formed like this: <protocol>://user:pass@serverAddress/applicationName/streamName.
 *  (e.g. rtmp://20.237.227.201/someApp/someStream
 */
@property (nonatomic, strong, readonly) NSString *streamURLString;

/**
 *  The custom URL string. Use this property to setup a streaming URL that doesn't conform
 *  with the standard "serverAddress/applicationName/streamName". 
 *  
 *  If the streaming URL is standrad, (<protocol>://serverAddress/applicationName/streamName)
 *  it is recommended to use the serverAddress, applicationName and streamName in order to 
 *  build the URL.
 */
@property (nonatomic, strong, readwrite) NSString *customStreamURLString;

/**
 *  The custom URL.
 */
@property (nonatomic, strong, readonly) NSURL *customStreamURL;

/**
 *  Returns YES if the customStreamURLString property is set to non empty value.
 */
@property (nonatomic, assign, readonly) BOOL usesCustomURL;

/// ----------------------------------------
/// @name Lifecycle
/// ----------------------------------------

/**
 *  Factory method for creating default stream info, using RTMP protocol.
 *
 *  @return The initialized object.
 */
+ (instancetype)streamInfo;

/**
 *  Factory method for creating default stream info, using RTMPS protocol.
 *
 *  @return The initialized object.
 */
+ (instancetype)secureStreamInfo;

@end
