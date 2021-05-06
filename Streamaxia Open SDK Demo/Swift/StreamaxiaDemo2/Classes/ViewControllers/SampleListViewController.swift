//
//  SampleListViewController.swift
//  StreamaxiaDemo2
//
//  Created by ShunFukumoto on 2020/05/22.
//  Copyright © 2020 Agilio. All rights reserved.
//

import Foundation

class SampleListViewController: UITableViewController {
    let kTableViewCellHeight : CGFloat = 88
    let kSampleTitleArray : [String] = ["Standard", "ARFaceTracking"]
    
    override func viewWillAppear(_ animated: Bool) {
        self.tableView.reloadData()
        super.viewWillAppear(animated)
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return kSampleTitleArray.count
    }
    
    override func tableView(_ table: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return kTableViewCellHeight
    }
        
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = UITableViewCell(style: .default, reuseIdentifier: "SampleTitle")
        cell.textLabel?.text = kSampleTitleArray[indexPath.row]
        
        return cell
    }
        
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let title = kSampleTitleArray[indexPath.row]
        performSegue(withIdentifier: "go\(title)ViewController", sender: nil)
    }
}
