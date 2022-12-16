// WANNA SDK
// Copyright © 2022 WANNABY Inc. All rights reserved.

import UIKit

protocol Coordinator: AnyObject {
    var childCoordinators: [Coordinator] { get }
    var navigationController: UINavigationController { get }

    func start()
}
