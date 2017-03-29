//
//  AXUtils+VideoOrientation.h
//  StreamaxiaSDK
//
//  Created by Mihaita Babici on 9/12/16.
//  Copyright © 2016 Agilio. All rights reserved.
//

@import Foundation;
@import AVFoundation;
@import UIKit;

#import "AXUtils.h"
#import "AXRecorderDefines.h"

@interface AXUtils (VideoOrientation)

@property (nonatomic, assign, readonly) UIInterfaceOrientation currentStatusBarOrientation;

@property (nonatomic, assign, readonly) AVCaptureVideoOrientation currentCaptureVideoOrientation;

@end
