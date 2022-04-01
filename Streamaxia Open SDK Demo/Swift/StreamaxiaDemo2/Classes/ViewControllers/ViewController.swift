//
//  ViewController.swift
//  StreamaxiaDemo2
//
//  Created by Roland Tolnay on 9/21/16.
//  Copyright © 2016 Streamaxia. All rights reserved.
//

import UIKit
import StreamaxiaSDK

// Modify this to your desired stream name
// Playback will be available at play.streamaxia.com/<your-stream-name>
let kStreamaxiaStreamName: String = "test"

/// View controller that displays some basic UI for capturing and streaming
/// live video and audio media.
class ViewController: UIViewController {
    
    // MARK: - Private Constants -
    
    fileprivate let kStartButtonTag: NSInteger = 0
    
    fileprivate let kStopButtonTag: NSInteger = 1
    
    // MARK: - Private Properties -
    
    @IBOutlet weak var startButton: UIButton!
    
    @IBOutlet weak var startLocalRecordButton: UIButton!
    
    @IBOutlet weak var leftLabel: UILabel!
    
    @IBOutlet weak var rightLabel: UILabel!
    
    @IBOutlet weak var leftRecordLabel: UILabel!
    
    @IBOutlet weak var rightRecordLabel: UILabel!
    
    @IBOutlet weak var infoLabel: UILabel!
    
    @IBOutlet weak var recorderView: UIView!
    
    @IBOutlet weak var overlayView: UIView!
    
    /// The recorder
    fileprivate var recorder: AXRecorder!
    
    /// The stream info
    fileprivate var streamInfo: AXStreamInfo!
    
    /// The recorder settings
    fileprivate var recorderSettings: AXRecorderSettings!
    
    // MARK: - View Lifecycle -
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.title = "StreamaxiaSDK Demo"
        
        self.setupUI()
        self.setupStreamaxiaSDK()
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
        if self.recorder.isActive {
            self.recorder.stopStreaming()
        }
    }
    
    // MARK: - Public methods -
    
    // MARK: - Actions -
    
    @IBAction func startButtonPressed(_ button: UIButton) {
        print("*** DEMO *** Recorder button pressed.")
        
        if (self.recorder == nil) {
            print("*** DEMO *** The recorder was not properly initialized.")
            
            return;
        }
        
        if (button.tag == self.kStartButtonTag) {
            print("*** DEMO *** START button pressed.")
            
            self.checkOrientation()
            
            self.recorder.startStreaming(completion: { (success, error) in
                print("*** DEMO *** The stream started with success: %@", success ? "YES" : "NO")
                
                if (success) {
                    DispatchQueue.main.async {
                        self.startButton.tag = self.kStopButtonTag
                        self.startButton.setTitle("Stop", for: .normal)
                    }
                    
                    DispatchQueue.main.asyncAfter(deadline: .now() + 5.0) {
                        self.takeSnapshot()
                    }
                } else {
                    print("*** DEMO *** Error: %@", error ?? "")
                }
            })
        } else if (button.tag == self.kStopButtonTag) {
            print("*** DEMO *** STOP button pressed.")
            
            self.startButton.tag = self.kStartButtonTag
            self.startButton.setTitle("Start", for: .normal)
            self.recorder.stopStreaming()
            self.updateLabel(time: 0.0)
        }
    }
    
    @IBAction func startLocalRecordButtonPressed(_ button: UIButton) {
        if (button.tag == self.kStartButtonTag) {
            print("*** DEMO *** START record button pressed.")
            
            self.checkOrientation()
            
            self.recorder.startRecording(completion: { (success, error) in
                print("*** DEMO *** The stream started with success: %@", success ? "YES" : "NO")
                
                if (success) {
                    DispatchQueue.main.async {
                        button.tag = self.kStopButtonTag
                        button.setTitle("Stop", for: .normal)
                        self.leftRecordLabel.text = "[Recording]"
                    }
                } else {
                    print("*** DEMO *** Error: %@", error ?? "")
                }
            })
        } else if (button.tag == self.kStopButtonTag) {
            print("*** DEMO *** STOP button pressed.")
            
            button.tag = self.kStartButtonTag
            button.setTitle("Start", for: .normal)
            self.recorder.stopRecording(completion: { success, error, url in
                print("*** DEMO *** The stream stopped with success: %@", success ? "YES" : "NO")
                DispatchQueue.main.async {
                    self.leftRecordLabel.text = "[Stopped]"
                }
            })
            self.updateRecordLabel(time: 0.0)
        }
    }
}

// MARK: - Private methods -

fileprivate extension ViewController {
    //#pragma mark - Private methods
    
    fileprivate func takeSnapshot() {
        recorder.takeSnapshot { (image, error) in
            if let image = image {
                print("Took a snapshot with:\(image.size)")
                // do something with the snapshot
            }
        }
    }
    
    fileprivate func defaultStreamInfo() -> AXStreamInfo {
        let info = AXStreamInfo.init()
        info.useSecureConnection = false
        
        info.customStreamURLString = "rtmp://rtmp.streamaxia.com/streamaxia/\(kStreamaxiaStreamName)"
        
//    Alternatively you can split the URL into its corresponding RTMP parts
//      info.serverAddress = "rtmp.streamaxia.com"
//      info.applicationName = "streamaxia"
//      info.streamName = kStreamaxiaStreamName;
        
        info.username = ""
        info.password = ""
        
        return info
    }
    
    fileprivate func defaultRecorderSettings() -> AXRecorderSettings {
        let utils = AXUtils.init()
        let settings = AXRecorderSettings.init()
        
        settings.videoFrameResolution = .standard720p
        settings.videoBitrate = utils.bitrate(for: settings.videoFrameResolution)
        settings.keyFrameInterval = Int(0.5 * Double(settings.frameRate))
        settings.exportLocalVideoToAssetLibrary = true
        
        return settings
    }
    
    
    fileprivate func setupStreamaxiaSDK() {
        let sdk = AXStreamaxiaSDK.sharedInstance()!
        
        //        Load the configuration certificate from the main bundle, standard URL
        
        //        NOTE: the .config and .key must be added to the project, with the name unchanged
        //        sdk.setupSDK(completion: { (success, error) in
        //            print("*** Streamaxia SDK *** Setup was completed with success: %@ \n*** error: %@", success ? "YES" : "NO", error ?? "")
        //
        //            // Printing StreamaxiaSDK status
        //            sdk.debugPrintStatus()
        //
        //            if (success) {
        //                DispatchQueue.main.async {
        //                    self.setupStreaming()
        //                }
        //            }
        //        })
        
        // Alternatively, a custom bundle can be used to load the certificate:
        let bundleURL = Bundle.main.url(forResource: "demo-certificate", withExtension: "bundle")
        let bundle = Bundle.init(url: bundleURL!)
        
        sdk.setupSDK(with: bundle?.bundleURL) { (success, error) in
            sdk.debugPrintStatus()
            
            if (success) {
                DispatchQueue.main.async {
                    self.setupStreaming()
                }
            }
        }
    }
    
    fileprivate func setupStreaming() {
        self.streamInfo = self.defaultStreamInfo()
        self.recorderSettings = self.defaultRecorderSettings()
        
        if let recorder = AXRecorder.init(streamInfo: self.streamInfo, settings: self.recorderSettings) {
            recorder.recorderDelegate = self
            recorder.setup(with: self.recorderView)
            recorder.prepareToRecord()
            
            var error: AXError?
            
            // Enable adaptive bitrate
            // Video quality will be adjusted based on available network and hardware resources
            recorder.activateFeatureAdaptiveBitRateWithError(&error)
            if error != nil {
                print("*** ERROR activating feature adaptive bitrate: \(error!.message)")
                error = nil
            }
            
            // Enable tap to focus
            // The focus and exposure will be adjusted based on your selection
            recorder.activateFeatureTapToFocus { (success, error) in
                guard success else {
                    print("*** ERROR activating feature tap to focus: \(error!.message)")
                    return
                }
            }
            
            self.recorder = recorder
        }
        
        // Printing some debug info about the initialiation settings
        let debugRecorderSettings = AXDebug.init().string(from: self.recorderSettings)
        let debugStreamInfo = AXDebug.init().string(from: self.streamInfo)
        
        print("*** DEMO **** Did set up the recorder with the following settings:\n%@\n%@", debugRecorderSettings!, debugStreamInfo!)
    }
    
    fileprivate func updateLabel(time: TimeInterval) {
        let t = Int(time)
        let s = t % 60
        let m = (t / 60) % 60
        let h = t / 3600
        
        let text = String.init(format: "T: %.2ld:%.2ld:%.2ld", Int(h), Int(m), Int(s))
        
        DispatchQueue.main.async {
            self.rightLabel.text = text
        }
    }
    
    fileprivate func updateRecordLabel(time: TimeInterval) {
        let t = Int(time)
        let s = t % 60
        let m = (t / 60) % 60
        let h = t / 3600
        
        let text = String.init(format: "T: %.2ld:%.2ld:%.2ld", Int(h), Int(m), Int(s))
        
        DispatchQueue.main.async {
            self.rightRecordLabel.text = text
        }
    }
    
    fileprivate func checkOrientation() {
        let currentOrientation: UIInterfaceOrientation = UIApplication.shared.statusBarOrientation
        var error: AXError? = nil
        if currentOrientation == .portrait {
            recorder.changeResolutionInversion(true, withError: &error)
        } else if currentOrientation != .portraitUpsideDown {
            recorder.changeResolutionInversion(false, withError: &error)
        }
        if error != nil {
            // Handle error
        }
    }
}

// MARK: - AXRecorderDelegate -

extension ViewController: AXRecorderDelegate {
    func recorder(_ recorder: AXRecorder!, didChange state: AXRecorderState) {
        print("*** DEMO *** Recorder State Changed to: \(state)")
        
        var string = "N/A"
        
        switch state {
        case .stopped:
            string = "[Stopped]"
        case .recording:
            string = "[Streaming]"
        case .starting:
            string = "[Starting...]"
        case .stopping:
            string = "[Stopping...]"
        case .collectingExtraData:
            string = "[Get Extra Data]"
        case .processingExtraData:
            string = "[Proc. Extra Data]"
        default:
            string = "[Unknown state]"
        }
        
        DispatchQueue.main.async {
            self.leftLabel.text = string
        }
    }
    
    func recorder(_ recorder: AXRecorder!, didUpdateStreamTime deltaTime: TimeInterval) {
        // Show the recording time in the right label
        DispatchQueue.main.async {
            self.updateLabel(time: deltaTime)
        }
    }
    
    func recorder(_ recorder: AXRecorder!, didUpdateRecordTime deltaTime: TimeInterval) {
        // Show the recording time in the right label
        DispatchQueue.main.async {
            self.updateRecordLabel(time: deltaTime)
        }
    }
    
    func recorder(_ recorder: AXRecorder!, didChange status: AXNetworkStatus) {
        print("*** DEMO *** did change network status: \(status)")
        
        var string = "Unknown network status"
        
        switch status {
        case .notReachable:
            string = "Lost internet connection"
        case .reachableViaWiFi:
            string = "Internet is reachable on wifi"
        case .reachableViaWWAN:
            string = "Internet is reachabale on Cellular"
        }
        
        DispatchQueue.main.async {
            self.infoLabel.text = string
        }
    }
    
    func recorder(_ recorder: AXRecorder!, didReceive info: AXInfo!) {
        print("*** DEMO *** did receive info: %@", info)
    }
    
    func recorder(_ recorder: AXRecorder!, didReceive warning: AXWarning!) {
        print("*** DEMO *** did receive warning: %@", warning)
    }
    
    func recorder(_ recorder: AXRecorder!, didReceiveError error: AXError!) {
        print("*** DEMO *** did receive error: %@", error)
    }
    
    func recorder(_ recorder: AXRecorder!, didUpdateBitrate bitrate: UInt) {
        print("*** DEMO *** streaming bitrate \(bitrate)")
    }
}

// MARK: - UI Setup -

fileprivate extension ViewController {
    
    private func infoFont() -> UIFont? {
        return UIFont.init(name: "AvenirNextCondensed-UltraLight", size: 14.0)
    }
    
    private func labelFont() -> UIFont? {
        return UIFont.init(name: "AvenirNextCondensed-Regular", size: 16.0)
    }
    
    private func buttonFont() -> UIFont? {
        return UIFont.init(name: "AvenirNextCondensed-Medium", size: 20.0)
    }
    
    fileprivate func setupUI() {
        self.setupMain()
        self.setupStartButton()
        self.setupStartLocalRecordButton()
        self.setupLeftLabel()
        self.setupLeftRecordLabel()
        self.setupRightLabel()
        self.setupRightRecordLabel()
        self.setupInfoLabel()
    }
    
    private func setupMain() {
        self.recorderView.backgroundColor = UIColor.white
        self.overlayView.backgroundColor = UIColor.black.withAlphaComponent(0.25)
        self.view.backgroundColor = UIColor.lightGray
    }
    
    private func setupStartButton() {
        let button: UIButton = self.startButton!
        
        button.layer.cornerRadius = self.startButton.frame.size.height * 0.5
        button.backgroundColor = UIColor.black
        button.tintColor = UIColor.white
        button.tag = self.kStartButtonTag
        button.titleLabel?.font = self.buttonFont()
        button.setTitle("Start streaming", for: .normal)
    }
    
    private func setupStartLocalRecordButton() {
        let button: UIButton = self.startLocalRecordButton!
        
        button.layer.cornerRadius = self.startLocalRecordButton.frame.size.height * 0.5
        button.backgroundColor = UIColor.black
        button.tintColor = UIColor.white
        button.tag = self.kStartButtonTag
        button.titleLabel?.font = self.buttonFont()
        button.setTitle("Start local record", for: .normal)
    }
    
    private func setupLeftLabel() {
        let label = self.leftLabel!
        
        label.font = self.labelFont()
        label.backgroundColor = UIColor.black.withAlphaComponent(0.8)
        label.text = "[N/A]"
        label.textColor = UIColor.white
    }
    
    private func setupLeftRecordLabel() {
        let label = self.leftRecordLabel!
        
        label.font = self.labelFont()
        label.backgroundColor = UIColor.black.withAlphaComponent(0.8)
        label.text = "[N/A]"
        label.textColor = UIColor.white
    }
    
    private func setupRightLabel() {
        let label = self.rightLabel!
        
        label.font = self.labelFont()
        label.backgroundColor = UIColor.black.withAlphaComponent(0.8)
        label.text = "T: 00:00:00"
        label.textColor = UIColor.white
    }
    
    private func setupRightRecordLabel() {
        let label = self.rightRecordLabel!
        
        label.font = self.labelFont()
        label.backgroundColor = UIColor.black.withAlphaComponent(0.8)
        label.text = "T: 00:00:00"
        label.textColor = UIColor.white
    }
    
    private func setupInfoLabel() {
        let label = self.infoLabel!
        
        label.font = self.infoFont()
        label.backgroundColor = UIColor.black.withAlphaComponent(0.4)
        label.text = ""
        label.textColor = UIColor.white
    }
}
