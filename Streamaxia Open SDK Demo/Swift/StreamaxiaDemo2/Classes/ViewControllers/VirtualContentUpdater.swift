//
//  VirtualContentUpdater.swift
//  StreamaxiaDemo2
//
//  Created by ShunFukumoto on 2020/05/22.
//  Copyright © 2020 Agilio. All rights reserved.
//

import Foundation
import ARKit

@available(iOS 11.0, *)
class VirtualContentUpdater: NSObject, ARSCNViewDelegate {
    var virtualFaceNode: SCNNode? {
        didSet {
            setupFaceNodeContent()
        }
    }
    private var faceNode: SCNNode?
    private let serialQueue = DispatchQueue(label: "com.example.serial-queue")

    private func setupFaceNodeContent() {
        guard let faceNode = faceNode else { return }
        for child in faceNode.childNodes {
            child.removeFromParentNode()
        }
        if let content = virtualFaceNode {
            faceNode.addChildNode(content)
        }
    }

    //MARK: - ARSCNViewDelegate
    func renderer(_ renderer: SCNSceneRenderer, didAdd node: SCNNode, for anchor: ARAnchor) {
        faceNode = node
        serialQueue.async {
            self.setupFaceNodeContent()
        }
    }
}
