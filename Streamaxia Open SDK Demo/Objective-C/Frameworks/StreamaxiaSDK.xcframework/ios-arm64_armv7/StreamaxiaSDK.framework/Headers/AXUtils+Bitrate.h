//
//  AXUtils+Bitrate.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/11/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

#import "AXUtils.h"
#import "AXRecorderDefines.h"

/**
 The bit rate utils.
 */
@interface AXUtils (Bitrate)

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 The list of optimal bit rates for each resolution.
 */
@property (nonatomic, strong, readonly) NSDictionary<NSNumber *, NSNumber *> *optimalBitrates;

/**
 The list of minimum bit rates for each resolution.
 */
@property (nonatomic, strong, readonly) NSDictionary<NSNumber *, NSNumber *> *minBitrates;

/**
 The list of maximum bit rates for each resolution.
 */
@property (nonatomic, strong, readonly) NSDictionary<NSNumber *, NSNumber *> *maxBitrates;

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

/**
 Provides the optimal bit rate for the given resolution.
 
 @param resolution The resolution
 
 @return The optimal bit rate, in bps.
 */
- (NSInteger)bitrateForResolution:(AXVideoFrameResolution)resolution;

/**
 Provides the minimum bit rate for the given resolution.
 
 @param resolution The resolution
 
 @return The minimum bit rate, in bps.
 */
- (NSInteger)minBitrateForResolution:(AXVideoFrameResolution)resolution;

/**
 Provides the maximum bit rate for the given resolution.
 
 @param resolution The resolution
 
 @return The maximum bit rate, in bps.
 */
- (NSInteger)maxBitrateForResolution:(AXVideoFrameResolution)resolution;

/**
 Clamps the given bit rate between the recommended minimum and maximum bit rate values,
 for the given resolution.
 
 The input bit rate should be in bits per second (bps).
 *
 @param bitrate    The bit rate.
 @param resolution The resolution
 
 @return The clamped bit rate, in bps.
 */
- (NSInteger)clampBitrate:(NSInteger)bitrate forResolution:(AXVideoFrameResolution)resolution;

@end
