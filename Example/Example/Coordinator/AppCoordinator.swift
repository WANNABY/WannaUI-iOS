// WANNA SDK
// Copyright © 2022 WANNABY Inc. All rights reserved.

import Foundation
import UIKit

final class AppCoordinator: Coordinator {
    var childCoordinators: [Coordinator] = []
    var navigationController: UINavigationController
    
    private lazy var modelsController: ModelsListViewController? = {
        let controllerId = String(describing: ModelsListViewController.self)
        let storyboard = UIStoryboard(name: controllerId, bundle: nil)
        guard let controller = storyboard.instantiateViewController(withIdentifier: controllerId) as? ModelsListViewController else {
            return nil
        }
        controller.set(viewModel: ModelsListViewModel())
        return controller
    }()

    private weak var window: UIWindow?

    init(window: UIWindow?, navigationController: UINavigationController) {
        self.window = window
        self.navigationController = navigationController
    }

    func start() {
        navigationController.setViewControllers([modelsController!], animated: false)
        window?.rootViewController = navigationController
        window?.makeKeyAndVisible()
    }
}
