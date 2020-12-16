//
//  AXLog.h
//  StreamaxiaSDK
//
//  Created by Razvan Chelemen on 06/03/2017.
//  Copyright © 2017 Agilio. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "AXSDKDefines.h"

#define AXLogError(log, ...) [AXLog.sharedInstance logError: [NSString stringWithFormat:log, ##__VA_ARGS__] scope:AXLogScopeAll];
#define AXLogWarning(log, ...) [AXLog.sharedInstance logWarning: [NSString stringWithFormat:log, ##__VA_ARGS__] scope:AXLogScopeAll];
#define AXLogInfo(log, ...) [AXLog.sharedInstance logInfo: [NSString stringWithFormat:log, ##__VA_ARGS__] scope:AXLogScopeAll];
#define AXLogDebug(log, ...) [AXLog.sharedInstance logDebug: [NSString stringWithFormat:log, ##__VA_ARGS__]];

#define AXLogBuffering(log, ...) [AXLog.sharedInstance logInfo: [NSString stringWithFormat:log, ##__VA_ARGS__] scope:AXLogScopeBuffering];
#define AXLogRTMP(log, ...) [AXLog.sharedInstance logInfo: [NSString stringWithFormat:log, ##__VA_ARGS__] scope:AXLogScopeRTMP];

/**
 Class used for logging. It handles the log writing the output source.
 */
@interface AXLog : NSObject

/**
 Singleton instance.
 */
@property (nonatomic, strong, class, readonly) AXLog *sharedInstance;

/**
 Current logging level. It filters the logs by importance, info, warning, error etc.
 */
@property (nonatomic, assign) AXLogLevel    logLevel;

/**
 Property used to control the log output.
 */
@property (nonatomic, assign) AXLogOutput   logOutput;

/**
 Property used to filter logs by the part of the streamer that presents interest.
 */
@property (nonatomic, assign) AXLogScope    logScope;

/**
 Log an error in a scope.
 
 @param log   The message to log.
 @param scope The scope of the message.
 */
- (void)logError:(NSString *)log scope:(AXLogScope)scope;

/**
 Log a warning in a scope.
 
 @param log   The message to log.
 @param scope The scope of the message.
 */
- (void)logWarning:(NSString *)log scope:(AXLogScope)scope;

/**
 Log info in a scope.
 
 @param log   The message to log.
 @param scope The scope of the message.
 */
- (void)logInfo:(NSString *)log scope:(AXLogScope)scope;

/**
 Log a warning in a scope.
 
 @param log   The message to log.
 @param scope The scope of the message.
 */
- (void)logDebug:(NSString *)log;

@end
