// WANNA SDK
// Copyright © 2022 WANNABY Inc. All rights reserved.

import Foundation
import WsneakersUISDK
import Combine

protocol ModelsListViewModelType {
    var title: String { get }
    var modelIdsPublisher: AnyPublisher<[String], Never> { get }
    var activityIndicatorIsAnimatingPublisher: AnyPublisher<Bool, Never> { get }
    var presentControllerPublisher: AnyPublisher<UIViewController, Never> { get }
    
    func loadModels()
    func didSelectModel(at indexPath: IndexPath)
}

final class ModelsListViewModel: ModelsListViewModelType {
    let title = "Bags"
    private let supportedTypes = ["bag"]
    private var storage: WsneakersUISDKRenderModelStorage?
    
    let modelIdsPublisher: AnyPublisher<[String], Never>
    private let modelIdsSubject = CurrentValueSubject<[String], Never>([])
    
    let activityIndicatorIsAnimatingPublisher: AnyPublisher<Bool, Never>
    private let activityIndicatorIsAnimatingSubject = PassthroughSubject<Bool, Never>()
    
    let presentControllerPublisher: AnyPublisher<UIViewController, Never>
    private let presentControllerSubject = PassthroughSubject<UIViewController, Never>()
    
    private var storageCreator: () throws -> WsneakersUISDKRenderModelStorage? = {
        try .createStorage(withConfig: Settings.license,
                           cacheSize: Settings.cacheSize)
    }

    private let storyboard: UIStoryboard
    
    init(storyboard: UIStoryboard? = nil) {
        modelIdsPublisher = modelIdsSubject.eraseToAnyPublisher()
        activityIndicatorIsAnimatingPublisher = activityIndicatorIsAnimatingSubject.eraseToAnyPublisher()
        presentControllerPublisher = presentControllerSubject.eraseToAnyPublisher()

        self.storyboard = storyboard ?? UIStoryboard(
            name: String(describing: BagProductDetailsPage.self),
            bundle: nil
        )
    }
    
    func loadModels() {
        activityIndicatorIsAnimatingSubject.send(true)
        
        DispatchQueue.global(qos: .userInitiated).async { [weak self] in
            do {
                try self?.storage = self?.makeStorage()
            } catch {
                DispatchQueue.main.async {
                    self?.handleStorageCreationError(error)
                }
            }
            guard let result = self?.storage?.loadModelsSync() else { return }
            DispatchQueue.main.async {
                self?.handleModelsResult(result)
            }
        }
    }
    
    func didSelectModel(at indexPath: IndexPath) {
        guard let productController = storyboard.instantiateInitialViewController(creator: { coder in
            let modelId = self.modelIdsSubject.value[indexPath.row]
            return BagProductDetailsPage(coder: coder, modelId: modelId)
        }) else {
            let alert = makeAlertController(withTitle: "Error",
                                            message: "Cannot create BagProductDetailsPage",
                                            retry: nil)
            presentControllerSubject.send(alert)
            return
        }
        productController.modalPresentationStyle = .fullScreen
        presentControllerSubject.send(productController)
    }
}

private extension ModelsListViewModel {
    func handleModelsResult(_ result: Result<[WsneakersUISDKModelInfo], Swift.Error>) {
        switch result {
        case .success(let models):
            onModelsLoaded(models)
        case .failure(let error):
            activityIndicatorIsAnimatingSubject.send(false)
            let alert = makeAlertController(withTitle: "Error",
                                            message: error.localizedDescription,
                                            retry: loadModels)
            presentControllerSubject.send(alert)
        }
    }
    
    func makeStorage() throws -> WsneakersUISDKRenderModelStorage? {
        try storageCreator()
    }
    
    func handleStorageCreationError(_ error: Error) {
        let alert = makeAlertController(withTitle: "Error",
                                        message: "Storage creation failed: \(error.localizedDescription)",
                                        retry: loadModels)
        presentControllerSubject.send(alert)
    }
    
    func onModelsLoaded(_ models: [WsneakersUISDKModelInfo]) {
        filterModels(models)
        activityIndicatorIsAnimatingSubject.send(false)
    }
    
    func filterModels(_ models: [WsneakersUISDKModelInfo]) {
        let filteredModels: [String] = Set(models
            .filter { supportedTypes.contains($0.renderModelType) }
            .map(\.renderModelID))
            .sorted(by: { $0.caseInsensitiveCompare($1) == .orderedAscending })
        modelIdsSubject.send(filteredModels)
    }
    
    func makeAlertController(withTitle: String, message: String, retry: (() -> ())?) -> UIAlertController {
        let alertController = UIAlertController(title: title, message: message, preferredStyle: .alert)
        alertController.addAction(UIAlertAction(title: "Cancel", style: .cancel))
        
        if let callback = retry {
            alertController.addAction(UIAlertAction(title: "Retry", style: .default, handler: { _ in
                callback()
            }))
        }
        
        return alertController
    }
}
