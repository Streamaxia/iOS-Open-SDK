//
//  Hat.swift
//  StreamaxiaDemo2
//
//  Created by ShunFukumoto on 2020/05/22.
//  Copyright © 2020 Agilio. All rights reserved.
//

import Foundation
import ARKit

@available(iOS 11.0, *)
class Pylon : SCNNode {
    let occlusionNode: SCNNode
    init(geometry : ARSCNFaceGeometry) {
        geometry.firstMaterial?.colorBufferWriteMask = []
        occlusionNode = SCNNode(geometry: geometry)
        occlusionNode.renderingOrder = -1
        
        super.init()
        
        addChildNode(occlusionNode)
        
        self.geometry = geometry

        guard let url = Bundle.main.url(forResource: "Pylon", withExtension: "scn", subdirectory: "FaceEffect.scnassets") else {fatalError("missing hat resource")}
        let node = SCNReferenceNode(url: url)!
        node.load()

        addChildNode(node)
    }

    public func update(withFaceAnchor anchor : ARFaceAnchor) {
        let faceGeometry = geometry as! ARSCNFaceGeometry
        faceGeometry.update(from: anchor.geometry)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("(#function) has not been implemented")
    }
}
