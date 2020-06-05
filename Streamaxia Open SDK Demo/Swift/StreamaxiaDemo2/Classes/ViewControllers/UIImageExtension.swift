//
//  UIImageExtension.swift
//  StreamaxiaDemo2
//
//  Created by ShunFukumoto on 2020/05/22.
//  Copyright © 2020 Agilio. All rights reserved.
//

import Foundation

extension UIImage {
    func resize(_ reSize: CGSize) -> UIImage? {
        let widthRatio  = reSize.width / size.width
        let heightRatio = reSize.height / size.height
        let ratio = widthRatio > heightRatio ? heightRatio : widthRatio
        let newSize = CGSize(width: size.width * ratio, height: size.height * ratio)
        let rect = CGRect(x: 0, y: 0, width: newSize.width, height: newSize.height)
        UIGraphicsBeginImageContextWithOptions(newSize, false, 1.0)
        self.draw(in: rect)
        let newImage = UIGraphicsGetImageFromCurrentImageContext()
        UIGraphicsEndImageContext()
        return newImage
    }
}
