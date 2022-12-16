// WANNA SDK
// Copyright © 2022 WANNABY Inc. All rights reserved.

import Foundation
import UIKit
import Combine

final class ModelsListViewController: UIViewController {
    @IBOutlet private var tableView: UITableView!
    @IBOutlet private var activityIndicator: UIActivityIndicatorView!

    private var viewModel: ModelsListViewModelType!
    
    private var bag: Set<AnyCancellable> = []
    
    func set(viewModel: ModelsListViewModelType) {
        self.viewModel = viewModel
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = viewModel.title
        bindViewModel()
        viewModel.loadModels()
    }
}

extension ModelsListViewController: UITableViewDelegate {
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        viewModel.didSelectModel(at: indexPath)
    }
}

private extension ModelsListViewController {
    func bindViewModel() {
        viewModel.modelIdsPublisher.sink(receiveValue: tableView.items { tableView, indexPath, modelId in
            let cell = tableView.dequeueReusableCell(withIdentifier: ModelCell.reuseIdentifier, for: indexPath) as! ModelCell
            cell.set(title: modelId)
            return cell
        }).store(in: &bag)
        
        viewModel.activityIndicatorIsAnimatingPublisher.sink { [weak self] isAnimating in
            isAnimating ? self?.activityIndicator.startAnimating() : self?.activityIndicator.stopAnimating()
        }.store(in: &bag)
        
        viewModel.presentControllerPublisher.sink { [weak self] controller in
            self?.present(controller, animated: true)
        }.store(in: &bag)
    }
}
