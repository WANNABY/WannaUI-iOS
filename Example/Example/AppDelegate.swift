// WANNA SDK
// Copyright © 2022 WANNABY Inc. All rights reserved.

import UIKit
import WannaUI

@main
class AppDelegate: UIResponder, UIApplicationDelegate {
    var window: UIWindow?
    
    private var coordinator: Coordinator?
    
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey : Any]? = nil) -> Bool {
        self.window = UIWindow(frame: UIScreen.main.bounds)

        coordinator = AppCoordinator(window: window,
                                     navigationController: UINavigationController())
        coordinator?.start()
        return true
    }

    func application(_ app: UIApplication, open url: URL, options: [UIApplication.OpenURLOptionsKey : Any] = [:]) -> Bool {

        // Don't add to production code.
        // For WANNA internal use only.
        if #available(iOS 13.0, *) {
            WannaDebug.deepLinkHandler.handleURL(url)
        }

        return true
    }
}

