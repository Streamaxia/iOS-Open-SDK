//
//  AGViewController.m
//  StreamaxiaDemo1
//
//  Created by Roland Tolnay on 9/21/16.
//  Copyright © 2016 Streamaxia. All rights reserved.
//

@import StreamaxiaSDK;

#import "AGViewController.h"

// Modify this to your desired stream name
// Playback will be avaiable at play.streamaxia.com/<your-stream-name>
NSString * const kStreamaxiaStreamName = @"9dd61f";

@interface AGViewController () <AXRecorderDelegate>

// IB Outlets
@property (nonatomic, weak) IBOutlet UIButton *startButton;
@property (nonatomic, weak) IBOutlet UILabel *leftLabel;
@property (nonatomic, weak) IBOutlet UILabel *rightLabel;
@property (nonatomic, weak) IBOutlet UILabel *infoLabel;
@property (nonatomic, weak) IBOutlet UIView *recorderView;
@property (nonatomic, weak) IBOutlet UIView *overlayView;

// StreamaxiaSDK
@property (nonatomic, strong, readwrite) AXRecorder *recorder;
@property (nonatomic, strong, readwrite) AXStreamInfo *streamInfo;
@property (nonatomic, strong, readwrite) AXRecorderSettings *recorderSettings;

@end

@interface AGViewController (UISetup)

@property (nonatomic, strong, readonly) UIFont *infoFont;
@property (nonatomic, strong, readonly) UIFont *labelFont;
@property (nonatomic, strong, readonly) UIFont *buttonFont;

- (void)setupUI;

@end

const NSInteger kAGStreamerVCStartButtonTag = 0;
const NSInteger kAGStreamerVCStopButtonTag = 1;

@implementation AGViewController

#pragma mark - Lifecycle

#pragma mark - View Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = @"StreamaxiaSDK Demo";
    
    [self setupUI];
    [self setupStreamaxiaSDK];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    if (self.recorder.isActive) {
        [self.recorder stopStreaming];
    }
}

#pragma mark - Properties

- (AXStreamInfo *)streamInfo {
    if (!_streamInfo) {
        AXStreamInfo *info = [AXStreamInfo streamInfo];
        info.useSecureConnection = NO;
        
        NSString *urlString = [NSString stringWithFormat:@"rtmp://rtmp.streamaxia.com/streamaxia/%@",kStreamaxiaStreamName];
        info.customStreamURLString = urlString;//@"rtmp://a.rtmp.youtube.com/live2/79jm-e43f-4v5t-573u";
        
//    Alternatively you can split the URL into its corresponding RTMP parts
//      info.serverAddress = @"rtmp.streamaxia.com";
//      info.applicationName = @"streamaxia";
//      info.streamName = kStreamaxiaStreamName;
        
        info.username = @"";
        info.password = @"";
        
        _streamInfo = info;
    }
    
    return _streamInfo;
}

- (AXRecorderSettings *)recorderSettings {
    if (!_recorderSettings) {
        AXUtils *utils = [AXUtils utils];
        AXRecorderSettings *settings = [AXRecorderSettings recorderSettings];
        settings.videoFrameResolution = AXVideoFrameResolutionStandard720p;
        settings.videoBitrate = [utils bitrateForResolution:settings.videoFrameResolution];
        settings.keyFrameInterval = 0.5 * settings.frameRate;
        
        _recorderSettings = settings;
    }
    
    return _recorderSettings;
}

#pragma mark - Public methods

#pragma mark - Private methods

- (void)takeSnapshot {
    [self.recorder takeSnapshotWithCompletion:^(UIImage *snapshot, AXError *error) {
        // do something with the image
    }];
}

- (void)setupStreamaxiaSDK {
    __weak typeof(self) weakSelf = self;
    AXStreamaxiaSDK *sdk = [AXStreamaxiaSDK sharedInstance];
    
    // Load the configuration certificate from the main bundle, standard URL
    
    // NOTE: the .config and .key must be added to the project, with the name unchanged
    //    [sdk setupSDKWithCompletion:^(BOOL success, AXError *error) {
    //        NSLog(@"*** Streamaxia SDK *** Setup was completed with success: %@ \n*** error: %@", success ? @"YES" : @"NO",      error);
    //
    //        // Printing StreamaxiaSDK status
    //        [sdk debugPrintSDKStatus];
    //
    //        if (success) {
    //            dispatch_async(dispatch_get_main_queue(), ^{
    //                [weakSelf setupStreaming];
    //            });
    //        }
    //    }];
    
    // Alternatively, a custom bundle can be used to load the certificate:
    NSURL *bundleURL = [[NSBundle mainBundle] URLForResource:@"demo-certificate" withExtension:@"bundle"];
    NSBundle *bundle = [NSBundle bundleWithURL:bundleURL];
    
    [sdk setupSDKWithURL:bundle.bundleURL withCompletion:^(BOOL success, AXError *error) {
        [sdk debugPrintSDKStatus];
        
        if (success) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [weakSelf setupStreaming];
            });
        }
    }];
}

- (void)setupStreaming {
    AXRecorder *recorder = [AXRecorder recorderWithStreamInfo:self.streamInfo settings:self.recorderSettings];
    recorder.recorderDelegate = self;
    
    [recorder setupWithView:self.recorderView];
    [recorder prepareToRecord];
    
    self.recorder = recorder;
    
    // Printing some debug info about the initialiation settings
    NSString *debugRecorderSettings = [[AXDebug debug] stringFromRecorderSettings:self.recorderSettings];
    NSString *debugStreamInfo = [[AXDebug debug] stringFromStreamInfo:self.streamInfo];
    
    NSLog(@"*** Did set up the recorder with the following settings:\n%@\n%@", debugRecorderSettings, debugStreamInfo);
    
    AXError *error = nil;
    
    // Turn on adaptive bitrate: video quality is adjusted based on network resources
    [self.recorder activateFeatureAdaptiveBitRateWithError:&error];
    if (error) {
        NSLog(@"*** ERROR activating feature adaptive bitrate: %@",error.message);
        error = nil;
    }
    
    // Turn on save locally: all streams are saved to the camera roll
    [self.recorder activateFeatureSaveLocallyWithError:&error];
    if (error) {
        NSLog(@"*** ERROR activating feature save locally: %@",error.message);
        error = nil;
    }
    
    [self.recorder activateFeatureTapToFocusWithCompletion:^(BOOL success, AXError *error) {
        if (!success) {
            NSLog(@"*** ERROR activating feature tap to facus: %@",error.message);
            error = nil;
        }
    }];
}

- (void)updateLabelWithTime:(NSTimeInterval)time {
    NSInteger t = (NSInteger)time;
    NSTimeInterval s = t % 60;
    NSTimeInterval m = (t / 60) % 60;
    NSTimeInterval h = t / 3600;
    
    NSString *text = [NSString stringWithFormat:@"T: %.2ld:%.2ld:%.2ld", (long)h, (long)m, (long)s];
    
    self.rightLabel.text = text;
}

/**
 Configures the recorder based on the current device orientation
 */
- (void)checkOrientation {
    UIInterfaceOrientation currentOrientation = [UIApplication sharedApplication].statusBarOrientation;
    AXError *error = nil;
    if (currentOrientation == UIInterfaceOrientationPortrait) {
        [self.recorder changeResolutionInversion:YES withError:&error];
    } else if (currentOrientation != UIInterfaceOrientationPortraitUpsideDown) {
        [self.recorder changeResolutionInversion:NO withError:&error];
    }
    if (error) {
        NSLog(@"*** ERROR changing resolution inverted: %@ ***",error);
    }
}

#pragma mark - AXRecorderDelegate

- (void)recorder:(AXRecorder *)recorder didChangeState:(AXRecorderState)state {
    NSLog(@"*** DEMO *** Recorder State Changed to: (%ld)", (long)state);
    
    NSString *string = @"N/A";
    
    switch (state) {
        case AXRecorderStateStopped:
            string = @"[Stopped]";
            break;
        case AXRecorderStateRecording:
            string = @"[Recording]";
            break;
        case AXRecorderStateStarting:
            string = @"[Starting...]";
            break;
        case AXRecorderStateStopping:
            string = @"[Stopping...]";
            break;
        case AXRecorderStateCollectingExtraData:
            string = @"[Get Extra Data]";
            break;
        case AXRecorderStateProcessingExtraData:
            string = @"[Proc. Extra Data]";
            break;
        default:
            string = @"[Unknown state]";
            break;
    }
    
    __weak typeof(self) weakSelf = self;
    
    // Show the recorder state in the left label
    dispatch_async(dispatch_get_main_queue(), ^{
        weakSelf.leftLabel.text = string;
    });
}

- (void)recorder:(AXRecorder *)recorder didUpdateStreamTime:(NSTimeInterval)deltaTime {
    __weak typeof(self) weakSelf = self;
    
    // Show the recording time in the right label
    dispatch_async(dispatch_get_main_queue(), ^{
        [weakSelf updateLabelWithTime:deltaTime];
    });
}

- (void)recorder:(AXRecorder *)recorder didChangeNetworkStatus:(AXNetworkStatus)status {
    NSLog(@"*** DEMO *** did change network status: %ld", (long)status);
    
    NSString *string = @"";
    
    switch (status) {
        case AXNetworkStatusNotReachable:
            string = @"Lost internet connection";
            break;
        case AXNetworkStatusReachableViaWiFi:
            string = @"Internet is reachable on wifi";
            break;
        case AXNetworkStatusReachableViaWWAN:
            string = @"Internet is reachabale on Cellular";
            break;
            
        default:
            break;
    }
    
    __weak typeof(self) weakSelf = self;
    
    // Show the recording time in the right label
    dispatch_async(dispatch_get_main_queue(), ^{
        weakSelf.infoLabel.text = string;
    });
}

- (void)recorder:(AXRecorder *)recorder didReceiveInfo:(AXInfo *)info {
    NSLog(@"*** DEMO *** did receive info: %@", info);
}

- (void)recorder:(AXRecorder *)recorder didReceiveWarning:(AXWarning *)warning {
    NSLog(@"*** DEMO *** did receive warning: %@", warning);
}

- (void)recorder:(AXRecorder *)recorder didReceiveError:(AXError *)error {
    NSLog(@"*** DEMO *** did receive error: %@", error);
}

#pragma mark - Actions

- (IBAction)startButtonPressed:(UIButton *)button {
    NSLog(@"*** DEMO *** Recorder button pressed.");
    
    if (button.tag == kAGStreamerVCStartButtonTag) {
        NSLog(@"*** DEMO *** START button pressed.");
        
        // Setting broadcast resolution based on current orientation
        [self checkOrientation];
        
        __weak typeof(self) weakSelf = self;
        
        [self.recorder startStreamingWithCompletion:^(BOOL success, AXError *error) {
            NSLog(@"*** DEMO *** The stream started with success: %@", success ? @"YES" : @"NO");
            
            if (success) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    weakSelf.startButton.tag = kAGStreamerVCStopButtonTag;
                    [weakSelf.startButton setTitle:@"Stop" forState:UIControlStateNormal];
                });
                
                dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                    [self takeSnapshot];
                });
            } else {
                NSLog(@"*** DEMO *** Error: %@", error);
            }
        }];
    } else if (button.tag == kAGStreamerVCStopButtonTag) {
        NSLog(@"*** DEMO *** STOP button pressed.");
        
        self.startButton.tag = kAGStreamerVCStartButtonTag;
        [self.startButton setTitle:@"Start" forState:UIControlStateNormal];
        [self.recorder stopStreaming];
        [self updateLabelWithTime:0.0];
    }
}

@end

@implementation AGViewController (UISetup)

#pragma mark - Properties

- (UIFont *)infoFont {
    return [UIFont fontWithName:@"AvenirNextCondensed-UltraLight" size:12.0];
}

- (UIFont *)labelFont {
    return [UIFont fontWithName:@"AvenirNextCondensed-Regular" size:16.0];
}

- (UIFont *)buttonFont {
    return [UIFont fontWithName:@"AvenirNextCondensed-Medium" size:20.0];
}

#pragma mark - Public methods

- (void)setupUI {
    [self setupMain];
    [self setupStartButton];
    [self setupLeftLabel];
    [self setupRightLabel];
    [self setupInfoLabel];
}

#pragma mark - Private methods

- (void)setupMain {
    self.recorderView.backgroundColor = [UIColor whiteColor];
    self.overlayView.backgroundColor = [[UIColor blackColor] colorWithAlphaComponent:0.25];
    self.view.backgroundColor = [UIColor lightGrayColor];
}

- (void)setupStartButton {
    UIButton *button = self.startButton;
    
    button.layer.cornerRadius = self.startButton.frame.size.height * 0.5;
    button.backgroundColor = [UIColor blackColor];
    button.tintColor = [UIColor whiteColor];
    button.tag = kAGStreamerVCStartButtonTag;
    button.titleLabel.font = self.buttonFont;
    [button setTitle:@"Start" forState:UIControlStateNormal];
}

- (void)setupLeftLabel {
    UILabel *label = self.leftLabel;
    
    label.font = self.labelFont;
    label.backgroundColor = [[UIColor blackColor] colorWithAlphaComponent:0.8];
    label.text = @"[N/A]";
    label.textColor = [UIColor whiteColor];
}

- (void)setupRightLabel {
    UILabel *label = self.rightLabel;
    
    label.font = self.labelFont;
    label.backgroundColor = [[UIColor blackColor] colorWithAlphaComponent:0.8];
    label.text = @"T: 00:00:00";
    label.textColor = [UIColor whiteColor];
}

- (void)setupInfoLabel {
    UILabel *label = self.infoLabel;
    
    label.font = self.infoFont;
    label.backgroundColor = [[UIColor blackColor] colorWithAlphaComponent:0.4];
    label.text = @"";
    label.textColor = [UIColor whiteColor];
}

@end

