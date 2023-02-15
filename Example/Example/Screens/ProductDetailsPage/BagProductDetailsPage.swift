// WANNA SDK
// Copyright © 2022 WANNABY Inc. All rights reserved.

import UIKit
import WannaUI

final class BagProductDetailsPage: UIViewController {

    @IBOutlet private var previewContainer: UIView!
    @IBOutlet private var controlsContainer: UIView!

    private weak var modelsController: WannaModelsController?
    private let modelId: String

    init?(coder: NSCoder, modelId: String) {
        self.modelId = modelId
        super.init(coder: coder)
    }

    required init?(coder: NSCoder) {
        self.modelId = Settings.modelId
        super.init(coder: coder)
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        // Setup WannaSDK
        setupWannaSDK(modelId: modelId)

        // Do any additional setup after loading the view.
    }
}

// MARK: - Actions

private extension BagProductDetailsPage {
    @IBAction func onClose() {
        presentingViewController?.dismiss(animated: true)
    }
}

// MARK: - Wanna SDK integration

private extension BagProductDetailsPage {
    func setupWannaSDK(modelId: String) {

        // Parameters
        let license = Settings.license
        let cacheSizeBytes = UInt(Settings.cacheSize)

        // Start WannaUI SDK setup
        do {
            // Setup appearance
            let appearance: WannaAppearance = .default

            // Setup UI settings
            var uiSettings = WannaBags.UISettings()

            // Setup Onboarding
            uiSettings.onboarding.isDisabled = true
            uiSettings.onboarding.stepLocalizationHandler = { step in
                switch step {
                case .pinchToZoom:
                    return "Pinch to zoom"
                @unknown default:
                    assertionFailure("Unknown onboarding step: \(step)")
                    return ""
                }
            }
            
            // Setup loading animation
            uiSettings.loading.isHidden = false
            
            // Create config
            let config = try WannaConfig.builder
                .withCacheSize(bytes: cacheSizeBytes)
                .withLicense(license)
                .withAppearance(appearance)
                .build()

            // Setup flow
            let flow = WannaBags.Flow(config: config, modelId: modelId)
                .withControlsContainer(controlsContainer)
                .withProgressHandler { [weak self] progress in
                    // Handle model loading progress
                    self?.handleProgress(progress)
                }
                .withErrorHandler { [weak self] error in
                    // Handle setup errors
                    self?.handleError(error)
                }
                .withEventHandler { [weak self] event in
                    // Handle events
                    self?.handleEvent(event)
                }
                .withUISettings(uiSettings)

            // Start the flow
            let wannaViewController = try flow.start()

            // Present it to container view
            addChild(wannaViewController, to: previewContainer)

            // Save link to `modelsController` to update models later
            modelsController = flow.modelsController
        } catch {

            // Handle WannaUI setup errors
            print("WannaSDK setup failed with error: \(error)")
        }
    }

    func handleEvent(_ event: WannaBags.Event) {
        switch event {
        case .onModelLoaded(let modelId):
            print("On model loaded: \(modelId)")
        case .onDimensionsSwitched(let isActive):
            print("On dimensions switched state: \(isActive)")
        case .onPOISwitched(let index):
            print("On Point of Interest switched to index: \(index)")
        case .onRetry:
            print("On retry button tapped")
        @unknown default:
            assertionFailure("Unknown event: \(event)")
        }
    }

    func handleError(_ error: WannaBags.Error) {
        print(error.localizedDescription)
    }

    func handleProgress(_ progress: WannaProgress) {
        switch progress {
        case .loading(let progress):
            // Show progress view, update progress
            _ = progress

        case .finished:
            // Hide progress view
            break
        }
    }
}
