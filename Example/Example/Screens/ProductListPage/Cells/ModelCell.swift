// WANNA SDK
// Copyright © 2022 WANNABY Inc. All rights reserved.

import Foundation
import UIKit

final class ModelCell: UITableViewCell {
    @IBOutlet private var titleLabel: UILabel!
    
    func set(title: String) {
        titleLabel.text = title
    }
}

extension ModelCell {
    static var reuseIdentifier: String {
        return String(describing: self)
    }
}
