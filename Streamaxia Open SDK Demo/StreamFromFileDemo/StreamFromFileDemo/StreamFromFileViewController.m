//
//  StreamFromFileViewController.m
//  StreamFromFileDemo
//
//  Created by Razvan Chelemen on 29/10/2018.
//  Copyright © 2018 Streamaxia. All rights reserved.
//

#import "StreamFromFileViewController.h"

#import <StreamaxiaSDK/StreamaxiaSDK.h>

// Modify this to your desired stream name
// Playback will be avaiable at play.streamaxia.com/<your-stream-name>
NSString * const kStreamaxiaStreamName = @"testy";

@interface StreamFromFileViewController () <AXFileInputSourceDelegate, AXStreamSourceDelegate, AXStreamerDelegate>

@property (weak, nonatomic) IBOutlet UIView *videoView;
@property (weak, nonatomic) IBOutlet UIButton *startButton;

@property (nonatomic, strong) AXStreamer *streamer;
@property (nonatomic, strong) AXStreamSource *streamSource;
@property (nonatomic, strong) AXFileInputSource *inputSource;

@property (nonatomic, strong) AVSampleBufferDisplayLayer *videoLayer;

@end

@implementation StreamFromFileViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setup];
}

- (void)viewDidLayoutSubviews {
    [super viewDidLayoutSubviews];
    
    self.videoLayer.frame = self.videoView.bounds;
}

-(void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    [self.inputSource stopReading];
    [self.streamer stopStreaming];
    self.streamSource.on = NO;
}

#pragma mark - AXFileInputSourceDelegate methods

- (void)fileInputSource:(AXFileInputSource *)inputSource didReadVideoSample:(CMSampleBufferRef)sampleBuffer {
    [self.streamer sendVideoBuffer:sampleBuffer];
    
    CFArrayRef attachments = CMSampleBufferGetSampleAttachmentsArray(sampleBuffer, YES);
    CFMutableDictionaryRef dict = (CFMutableDictionaryRef)CFArrayGetValueAtIndex(attachments, 0);
    CFDictionarySetValue(dict, kCMSampleAttachmentKey_DisplayImmediately, kCFBooleanTrue);
    [self.videoLayer enqueueSampleBuffer:sampleBuffer];
    
    CFRelease(sampleBuffer);
}

- (void)fileInputSource:(AXFileInputSource *)inputSource didReadAudioSample:(CMSampleBufferRef)sampleBuffer {
    [self.streamer sendAudioBuffer:sampleBuffer];
}

#pragma mark - AXStreamSourceDelegate methods

- (void)streamSourceDidConnect:(AXStreamSource *)streamSource {
    
}

- (void)streamSourceDidDisconnect:(AXStreamSource *)streamSource {
    
}

- (void)streamSourceDidCloseConnection:(AXStreamSource *)streamSource {
    
}

- (void)streamSource:(AXStreamSource *)streamSource didFailConnectingWithError:(AXError *)error {
    
}

#pragma mark - AXStreamerDelegate methods

- (void)streamer:(AXStreamer *)streamer didChangeState:(AXStreamerState)state {
    if (state == AXStreamerStateStreaming) {
        [self.startButton setTitle:@"Stop" forState:UIControlStateNormal];
        [self.inputSource startReadingWithError:nil];
        self.streamSource.on = YES;
    } else if (state == AXStreamerStateStopping) {
        [self.startButton setTitle:@"Start" forState:UIControlStateNormal];
        [self.inputSource stopReading];
        self.streamSource.on = NO;
    }
}

- (void)streamer:(AXStreamer *)streamer didReceiveWarning:(AXWarning *)error {
    
}

- (void)streamer:(AXStreamer *)streamer didReceiveError:(AXError *)error {
    
}

#pragma mark - Actions

- (IBAction)didTapStartButton:(id)sender {
    if (self.streamer.currentState == AXStreamerStateStreaming) {
        [self.streamer stopStreaming];
        
    } else {
        [self.streamer startStreamingWithCompletion:nil];
    }
}

#pragma mark - Private methods

- (void)setup {
    self.videoLayer = [[AVSampleBufferDisplayLayer alloc] init];
    self.videoLayer.videoGravity = AVLayerVideoGravityResizeAspect;
    [self.videoView.layer addSublayer:self.videoLayer];
    
    self.streamer = [AXStreamer new];
    self.streamer.delegate = self;
    [self.streamer.videoSettings setResolution:AXVideoFrameResolutionSize1920x1080 withError:nil];
    [self.streamer.audioSettings setChannelsNumber:1 withError:nil];
    [self.streamer.audioSettings setSampleRate:44100 withError:nil];
    NSError *error = nil;
    [self.streamer.settings setLocalSave:YES withError:&error];
    //[self.streamer.videoSettings setResolutionInverted:YES withError:nil];
    
    AXStreamInfo *streamInfo = [AXStreamInfo new];
    NSString *urlString = [NSString stringWithFormat:@"rtmp://rtmp.streamaxia.com/streamaxia/%@",kStreamaxiaStreamName];
    streamInfo.customStreamURLString = urlString;
    self.streamSource = [self.streamer addStreamSourceWithInfo:streamInfo];
    self.streamSource.delegate = self;
    
    self.inputSource = [AXFileInputSource new];
    self.inputSource.delegate = self;
    self.inputSource.videoURL = self.movie.url;
}

@end
