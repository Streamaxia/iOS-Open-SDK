//
//  AXStreamSource.h
//  StreamaxiaSDK
//
//  Created by Razvan Chelemen on 15/02/2017.
//  Copyright © 2017 Agilio. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AXStreamSource;

/**
 Stream source delegate. Can be used to receive the status of a particular source.
 */
@protocol AXStreamSourceDelegate <NSObject>

@optional
/**
 Called after the stream source successfully connected to the server. If the stream source cannot connect to the server, this method is never called.
 
 @param streamSource  The stream source.
 */
- (void)streamSourceDidConnect:(AXStreamSource *)streamSource;

/**
 Called after the stream source disconnected from the server. This might happen from various reasons, for instance if the internet connection is lost.
 
 @param streamSource  The stream source.
 */
- (void)streamSourceDidDisconnect:(AXStreamSource *)streamSource;

/**
 Called if the connection is closed. This happens when the on property is set NO.
 
 @param streamSource  The stream source.
 */
- (void)streamSourceDidCloseConnection:(AXStreamSource *)streamSource;

/**
 Called if an error occurrs while connecting. This can happen when the on property is set YES.
 
 @param streamSource  The stream source.
 */
- (void)streamSource:(AXStreamSource *)streamSource didFailConnectingWithError:(AXError *)error;

@end

/**
 Represents a connection to a streaming server.
 */
@interface AXStreamSource : NSObject <NSCopying>

/**
 The stream source delegate.
 */
@property (nonatomic, weak) id<AXStreamSourceDelegate> delegate;

/**
 Connection details. This object must be set to provide the source required information about the server, such as URL, authentication, etc.
 */
@property (nonatomic, strong) AXStreamInfo *streamInfo;

/**
 Establishes/closes connection to server.
 */
@property (nonatomic, assign) BOOL on;

@end
