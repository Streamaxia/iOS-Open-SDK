//
//  AXLogSettings.h
//  StreamaxiaSDK
//
//  Created by Razvan Chelemen on 06/03/2017.
//  Copyright © 2017 Agilio. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class can be used to set/change the logging settings.
 */
@interface AXLogSettings : NSObject

/**
 The logging level. This property can be used to change the amount of logs by importance. It can also be used to turn logging off.
 */
@property (nonatomic, assign) AXLogLevel logLevel;

/**
 The logging output. Where the logs should go.
 */
@property (nonatomic, assign) AXLogOutput logOutput;

/**
 The logging scope. If the log level allows info logs, this property can be used to log info just from a specific part of the library.
 */
@property (nonatomic, assign) AXLogScope logScope;

@end
