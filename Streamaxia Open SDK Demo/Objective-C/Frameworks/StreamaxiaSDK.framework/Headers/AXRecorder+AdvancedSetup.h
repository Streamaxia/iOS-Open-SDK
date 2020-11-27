//
//  AXRecorder+AdvancedSetup.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/17/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;
@import AVFoundation;

#import "AXRecorder.h"

@interface AXRecorder (AdvancedSetup)

/// ----------------------------------------
/// @name Properties
/// ----------------------------------------

/**
 Get the currently active camera. This can be used to determine the current camera
 capabilities - like frame rate, resolutions and other.

 Also it can be used to set several other configuration settings. However, this
 should be used with care, since the streaming may be broken if some settings
 are changed while the streaming is running.
 */
@property (nonatomic, strong, readonly) AVCaptureDevice *currentCamera;

@property (nonatomic, strong, readonly) AVCaptureSession *currentSession;

/// ----------------------------------------
/// @name Public methods
/// ----------------------------------------

@end
