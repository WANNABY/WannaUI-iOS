// WANNA SDK
// Copyright © 2023 WANNABY Inc. All rights reserved.

import Foundation
import WsneakersUISDK

public extension WsneakersUISDKRenderModelStorage {
    func fetchModels(completion: @escaping (Result<[WsneakersUISDKModelInfo], Swift.Error>) -> Void) {
        loadModels { models, error in
            guard let models = models else {
                completion(.failure(error ?? Error.unexpected))
                return
            }
            completion(.success(models))
        }
    }
}
