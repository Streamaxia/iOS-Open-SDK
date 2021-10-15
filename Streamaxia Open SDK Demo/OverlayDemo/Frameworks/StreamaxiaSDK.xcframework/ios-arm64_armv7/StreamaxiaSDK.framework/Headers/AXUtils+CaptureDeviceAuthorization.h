//
//  AXUtils+CaptureDeviceAuthorization.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/15/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;
@import AVFoundation;

#import "AXUtils.h"

/**
 The AVCaptureDevice authorization status utils.
 */
@interface AXUtils (CaptureDeviceAuthorization)

/**
 Returns the microphone authorization status.
 */
@property (nonatomic, assign, readonly) AVAuthorizationStatus microphoneStatus;

/**
 Returns the camera authorization status.
 */
@property (nonatomic, assign, readonly) AVAuthorizationStatus cameraStatus;

/**
 Returns YES if the microphone was authorized.
 */
@property (nonatomic, assign, readonly) BOOL hasAccessToMicrophone;

/**
 Returns YES if the microphone access has been determined.
 */
@property (nonatomic, assign, readonly) BOOL hasDeterminedAccessToMicrophone;

/**
 Returns YES if the camera was authorized.
 */
@property (nonatomic, assign, readonly) BOOL hasAccessToCamera;

/**
 Returns YES if the camera access has been determined.
 */
@property (nonatomic, assign, readonly) BOOL hasDeterminedAccessToCamera;

@end
