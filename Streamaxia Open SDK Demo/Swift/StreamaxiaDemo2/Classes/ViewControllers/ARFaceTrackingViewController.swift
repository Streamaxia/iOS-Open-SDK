//
//  ARFaceTrackingViewController.swift
//  StreamaxiaDemo2
//
//  Created by ShunFukumoto on 2020/05/22.
//  Copyright © 2020 Agilio. All rights reserved.
//

import Foundation
import ARKit

@available(iOS 11.0, *)
class ARFaceTrackingViewController: UIViewController {
    @IBOutlet weak var sceneView: ARSCNView!
    
    var streamer: AXStreamer!
    var streamSource: AXStreamSource!
    var streamInfo: AXStreamInfo!

    let contentUpdater = VirtualContentUpdater()
    
    let kCameraFrameRate: Int32 = 30

    override func viewDidLoad() {
        super.viewDidLoad()
        setupStreamaxiaSDK()
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        UIApplication.shared.isIdleTimerDisabled = true
        startSession()
    }
    
    override func viewDidDisappear(_ animated: Bool) {
        super.viewDidDisappear(animated)
        self.sceneView.session.pause()
    }
    
    func setupStreamaxiaSDK() {
        let sdk = AXStreamaxiaSDK.sharedInstance()!
        
        let bundleURL = Bundle.main.url(forResource: "demo-certificate", withExtension: "bundle")
        let bundle = Bundle.init(url: bundleURL!)
        
        sdk.setupSDK(with: bundle?.bundleURL) { (success, error) in
            sdk.debugPrintStatus()
            
            if (success) {
                DispatchQueue.main.async {
                    self.setupCamera()
                }
            }
        }
    }
    
    func setupCamera() {
        self.sceneView.preferredFramesPerSecond = Int(kCameraFrameRate)
        self.contentUpdater.virtualFaceNode = self.createFaceNode()

        self.streamer = AXStreamer.init()
        self.streamer.delegate = self
        
        self.streamer.videoSettings.setResolution(.standard1080p, withError: nil)
        self.streamer.videoSettings.setResolutionInverted(true, withError: nil)
        self.streamer.videoSettings.setSendingVideo(true, withError: nil)
        
        self.streamer.audioSettings.setChannelsNumber(1, withError: nil)
        self.streamer.audioSettings.setSampleRate(44100, withError: nil)
        self.streamer.audioSettings.setSendingAudio(true, withError: nil)
        
        self.streamInfo = AXStreamInfo.init()
        self.streamInfo.useSecureConnection = false
        self.streamInfo.customStreamURLString = "rtmp://rtmp.streamaxia.com/streamaxia/\(kStreamaxiaStreamName)"
        self.streamInfo.username = ""
        self.streamInfo.password = ""
        
        self.streamSource = self.streamer.addStreamSource(with: self.streamInfo)
    
        self.sceneView.delegate = contentUpdater
        self.sceneView.session.delegate = self
        self.sceneView.automaticallyUpdatesLighting = true
        
        self.streamer.startStreaming(completion: nil)
        
        let debugStreamInfo = AXDebug.init().string(from: self.streamInfo)
        
        print("*** DEMO **** Did set up the recorder with the following settings: %@", debugStreamInfo!)
    }

    public func createFaceNode() -> SCNNode? {
        guard
            let device = self.sceneView.device,
            let geometry = ARSCNFaceGeometry(device : device, fillMesh: true) else {
            return nil
        }

        return Pylon(geometry: geometry)
    }

    func startSession() {
        guard ARFaceTrackingConfiguration.isSupported else { return }
        
        let configuration = ARFaceTrackingConfiguration()
        configuration.providesAudioData = true
        configuration.isLightEstimationEnabled = true
        
        self.sceneView.session.run(configuration, options: [.resetTracking, .removeExistingAnchors])
    }
    
    func convertFromCIImageToCVPixelBuffer (ciImage:CIImage) -> CVPixelBuffer? {
        let size: CGSize = ciImage.extent.size
        var pixelBuffer: CVPixelBuffer?
        let options = [
            kCVPixelBufferCGImageCompatibilityKey as String: true,
            kCVPixelBufferCGBitmapContextCompatibilityKey as String: true,
            kCVPixelBufferIOSurfacePropertiesKey as String: [:]
            ] as [String : Any]
        
        let status:CVReturn = CVPixelBufferCreate(kCFAllocatorDefault,
                                                  Int(size.width),
                                                  Int(size.height),
                                                  kCVPixelFormatType_32BGRA,
                                                  options as CFDictionary,
                                                  &pixelBuffer)
        
        let ciContext = CIContext()
        if (status == kCVReturnSuccess && pixelBuffer != nil) {
            ciContext.render(ciImage, to: pixelBuffer!)
        }
        
        return pixelBuffer
    }
}

@available(iOS 11.0, *)
extension ARFaceTrackingViewController: ARSessionDelegate {
    //MARK: - ARSession Delegate
    func session(_ session: ARSession, didFailWithError error: Error) {
        guard error is ARError else { return }
        print("SESSION ERROR")
    }
    func sessionWasInterrupted(_ session: ARSession) {
        print("SESSION INTERRUPTED")
    }
    func sessionInterruptionEnded(_ session: ARSession) {
        print("SESSION INTERRUPTION ENDED")
    }
    func session(_ session: ARSession, didOutputAudioSampleBuffer audioSampleBuffer: CMSampleBuffer) {
        self.streamer.sendAudioBuffer(audioSampleBuffer)
    }
    func session(_ session: ARSession, didUpdate frame: ARFrame) {
        let uiImage = self.sceneView.snapshot()
        let size = CGSize(
            width: uiImage.size.width / 4,
            height: uiImage.size.height / 4
        )
        let cgImage = uiImage.resize(size)!.cgImage!
        let ciImage = CIImage(cgImage: cgImage)
        let pixelBuffer = self.convertFromCIImageToCVPixelBuffer(ciImage: ciImage)!
        
        var formatDescription: CMFormatDescription?
        CMVideoFormatDescriptionCreateForImageBuffer(kCFAllocatorDefault, pixelBuffer, &formatDescription)

        let scale = CMTimeScale(NSEC_PER_SEC)
        let pts = CMTime(value: CMTimeValue(frame.timestamp * Double(scale)),
                         timescale: scale)
        var timingInfo = CMSampleTimingInfo(duration: kCMTimeInvalid,
                                            presentationTimeStamp: pts,
                                            decodeTimeStamp: kCMTimeInvalid)

        var newSampleBuffer: CMSampleBuffer?
        CMSampleBufferCreateForImageBuffer(kCFAllocatorDefault, pixelBuffer, true, nil,
                                           nil, formatDescription!, &timingInfo, &newSampleBuffer)

        self.streamer.sendVideoBuffer(newSampleBuffer)
    }
}

@available(iOS 11.0, *)
extension ARFaceTrackingViewController: AXStreamerDelegate {
    func streamer(_ streamer: AXStreamer!, didChange state: AXStreamerState) {
        switch state {
        case .starting:
            print("starting")
        case .stopped:
            print("stopped")
        case .stopping:
            print("stopping")
        case .streaming:
            print("streaming")
            self.streamSource.on = true
        default:
            print("others")
        }
    }
    
    func streamer(_ streamer: AXStreamer!, didReceive warning: AXWarning!) {
        print(warning.debugDescription)
    }
    
    func streamer(_ streamer: AXStreamer!, didReceiveError error: AXError!) {
        print(error.debugDescription)
    }
}

