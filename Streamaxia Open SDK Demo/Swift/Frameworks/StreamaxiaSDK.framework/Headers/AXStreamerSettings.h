//
//  AXStreamerSettings.h
//  StreamaxiaSDK
//
//  Created by Razvan Chelemen on 08/03/2017.
//  Copyright © 2017 Agilio. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "AXError.h"

/**
 The streamer streaming settings.
 */
@interface AXStreamerSettings : NSObject

/**
 Default settings.
 */
+ (instancetype)defaultSettings;

/**
 Property used to access the local save setting.
 */
@property (nonatomic, readonly) BOOL    localSave;

/**
 Property used to enable/disable local save.
 */
@property (nonatomic, assign) BOOL      adaptiveBitrate;

/**
 Method used to set the local save for the stream.
 
 @param enabled  Boolean used to enable/disable local save.
 @param error    Output error. It will be set if the setting could not be set.
 */
- (void)setLocalSave:(BOOL)enabled withError:(AXError **)error;

/**
 Method used to set adaptive bitrate for the stream

 @param adaptiveBitrate Boolean used to enable/disable adaptive bitrate
 @param error Output error. It will be set if the setting could not be set.
 */
- (void)setAdaptiveBitrate:(BOOL)adaptiveBitrate withError:(AXError **)error;

@end
