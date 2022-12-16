# Get started with WANNA UI SDK

<!-- TOC -->
- [Requirements and limitations](#requirements-and-limitations)
- [Demo app](#demo-app)
- [Installation](#installation)
    * [Cocoapods](#cocoapods)
- [Create your own app](#handle-events)
- [Handle events](#handle-events)
- [Handle errors](#handle-errors)
- [Customization](#customization)
    * [Custom progress](#custom-progress)
    * [Custom errors](#custom-errors)
    * [Onboarding](#onboarding)
- [Localization & internalization](#localization-internalization)
    * [Size Inches/centimeters](#size-inches-centimeters)
    * [Can hold widget](#can-hold-widget)
    * [Onboarding](#onboarding-1)
    <!-- * [Point of interest (POI)](#point-of-interest-poi) -->

<!-- /TOC -->

WANNA UI SDK enhances your iOS app with 3D Viewer for handbags.

WANNA’s 3D Viewer for handbags was specifically crafted to answer the industry’s pain point — the high number of returns due to the wrong size of the bag. It provides users with a novel experience to understand the size and capacity of a bag and enables brands to showcase the product with the utmost realism. Such an experience is designed to help clients make an informed shopping decision by exploring the product's size, dimensions, texture, and key attributes before purchase.

## Requirements and limitations

Supported environments:
* iOS 14 and later

## Demo app
* A [demo application](https://github.com/WANNABY/WannaUI-iOS/tree/master/Example) showing the integration of our SDK using cocoapods.

## Installation

Add WannaUI to your project as a cocoapods.

### Cocoapods

Create a Podfile if you haven't yet:

```
$ cd <your-project-directory>
$ pod init
```

Add `pod WannaUI` to your Podfile:

```
source 'https://github.com/CocoaPods/Specs.git'

platform :ios, '13.0'

inhibit_all_warnings!
use_frameworks!

target 'MyApp' do
  pod 'WannaUI'
end
```

Install the pod:

```
$ pod install
```

Open **Example/Example.xcworkspace** file in Xcode.

**NOTE:** when you open Example.**xcodeproj** instead of Example.**xcworkspace** it will result in compiler error **No such module ‘WsneakersUISDK’**


## Create your own app with 3D viewer

Create new or open existing Xcode project. Create new **UIViewController**.

1. (optional) Check if the current environment supports WANNA SDK. It depends on the device or iOS version. You may want to hide the 3D button in unsupported environments.<br>

```swift
guard WannaBags.Flow.isDeviceSupported else {
    return "Device is unsupported"
}
```

2. Create the SDK config<br>

```swift
let config = try WannaConfig.builder
    .withCacheSize(megabytes: 200)
    .withLicense("PUT_YOUR_LICENSE_HERE")
    .build()
```

In case you don't have a valid licence please contact [account@wanna.fashion](mailto:account@wanna.fashion)

3. Setup flow<br>

```swift
let flow = WannaBags.Flow(config: config, modelId: "PUT_YOUR_MODEL_ID_HERE")
    .withErrorHandler { error in
        // handle errors here
    }
    .withEventHandler { event in
        // handle events here
    }
    .withProgressHandler { progress in
        // Handle progress here
    }
```

4. Start the flow and present preview view controller<br>

```swift
let wannaViewController = try flow.start()
present(wannaViewController, animated: true)
```

5. (optional) To present content in view instead of fullscreen first implement extension:<br>

```swift
extension UIViewController {
    func addChild(_ childController: UIViewController, to view: UIView?) {
        let view: UIView = view ?? self.view

        childController.willMove(toParent: self)

        addChild(childController)
        view.addSubview(childController.view)
        view.addBorderConstraints(to: childController.view)

        childController.didMove(toParent: self)
    }
}  
```

Then add `wannaViewController` to parent view:<br>

```swift
let wannaViewController = try flow.start()
addChild(wannaViewController, to: previewContainer)
```

6. Full code sample

```swift

func viewDidLoad() {
    super.viewDidLoad()

    do {
        // Setup WannaSDK
        try setupWannaSDK()
    } catch {
        // Setup failed
    }
}

func setupWannaSDK() throws {
    // Create config
    let config = try WannaConfig.builder
        .withCacheSize(megabytes: 200)
        .withLicense("PUT_YOUR_LICENSE_HERE")
        .build()

    // Setup flow
    let flow = WannaBags.Flow(config: config, modelId: "PUT_YOUR_MODEL_ID_HERE")
        .withProgressHandler { progress in
            // Handle progress here
        }
        .withErrorHandler { error in
            // Handle errors here
        }
        .withEventHandler { event in
            // Handle events here
        }

    // Start the flow
    let wannaViewController = try flow.start()

    // Present it to container view
    present(wannaViewController, animated: true)
}
```


## Handle events

WANNA UI SDK allows you to track technical events:

1. Implement event handler

```swift
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
    }
}
```

2. Pass event handler to the flow

```swift
WannaBags.Flow(config: config, modelId: "PUT_YOUR_MODEL_ID_HERE")
    .withEventHandler { [weak self] event in
        self?.handleEvent(event)
    }
```

| Event     |    Description    |
| -----|-------|
| `.onModelLoaded(modelId: String)` | Model is loaded successfully. |
| `.onDimensionsSwitched(toActive: Bool)` | On dimensions button switched. |
| `.onPOISwitched(toIndex: String)` | On point of interest (POI) switched. |
| `.onRetry` | User tapped on retry button. |


## Handle errors

WANNA UI SDK allows you to handle errors:

1. Implement error handler

```swift
func handleError(_ error: WannaBags.Error) {
    print("On Wanna SDK error: \(error)")
}
```

2. Pass error handler to the flow

```swift
WannaBags.Flow(config: config, modelId: "PUT_YOUR_MODEL_ID_HERE")
    .withErrorHandler { [weak self] error in
        self?.errorHandler(error)
    }
```

| Error     |    Description    |
| -----|-------|
| `.setModelFailed(modelId: String)` | Error during model update. |
| `.initializationFailed(error: Error)` | Initialization is failed. |


## Customization

WANNA 3D Viewer provides default implementation but allows you to customize visual appearance.


### Custom progress

Implement your custom progress view:

1. Setup progress handler to update actual progress:

```swift
func handleProgress(_ progress: WannaProgress) {
    switch progress {
    case .loading(let progress):
        // Show progress view, update progress
        self?.progressView.isHidden = true
        self?.progressView.progress = progress

    case .finished:
        // Hide progress view
        self?.progressView.isHidden = false
    }
}
```

2. Hide default loading view & pass custom progress handler to the flow

```swift
var uiSettings = WannaBags.UISettings()
uiSettings.loading.isHidden = true

WannaBags.Flow(config: config, modelId: "PUT_YOUR_MODEL_ID_HERE")
    .withUISettings(uiSettings)
    .withProgressHandler { [weak self] progress in
        self?.handleProgress(progress)
    }
```


### Custom errors

Implement your custom `errorView`. Then integrate it to the SDK:

1. Implement retry handler:

```swift
func onRetry() {
    flow.retry()
    errorView.isHidden = true
}
```

2. Hide default error view & pass custom error handler to the flow

```swift
var uiSettings = WannaBags.UISettings()
uiSettings.error.isHidden = true

WannaBags.Flow(config: config, modelId: "PUT_YOUR_MODEL_ID_HERE")
    .withUISettings(uiSettings)
    .withErrorHandler { [weak self] error in
        // Handle error
        errorView.isHidden = false
    }
```


## Localization & internalization

WANNA 3D Viewer allows you to localize all the text labels as well as set some specific content for displaying models.


### Size centimeters/inches

A model can contain information about its dimensions in inches and centimetres. This info will be displayed in the 3D Viewer when the user taps on the corresponding UI button. Units used depends on user’s device locale. It is the same as `Locale.current.usesMetricSystem`. You can always update this setting.

```swift
var appearance: WannaAppearance = .default
appearance.usesMetricSystem = true/false

let config = try WannaConfig.builder
    .withLicense("PUT_YOUR_LICENSE_HERE")
    .withAppearance(appearance)
    .build()            
```


### Can hold widget

 You can localize the title for the widget that displays items which can be put inside a bag. The names of items aren’t localizable - this functionality will be supported in the next versions of the 3D Viewer.

```swift
var uiSettings = WannaBags.UISettings()
uiSettings.canHold.title = NSLocalizedString("Can hold", comment: "WannaSDK: Can hold widget")

WannaBags.Flow(config: config, modelId: "PUT_YOUR_MODEL_ID_HERE")
    .withUISettings(uiSettings)
```


### Onboarding

To enhance user’s experience, WANNA 3D Viewer can show onboarding screens to explain some available interactions with a model. SDK launches these onboarding screens when the user utilizes the 3D Viewer for the first time.

#### Hide onboarding

It's possible to disable onboarding.

```swift
var uiSettings = WannaBags.UISettings()
uiSettings.onboarding.isDisabled = true

WannaBags.Flow(config: config, modelId: "PUT_YOUR_MODEL_ID_HERE")
    .withUISettings(uiSettings)
```

#### Localize titles

You can localize the labels for the onboarding widget

```swift
var uiSettings = WannaBags.UISettings()
uiSettings.onboarding.stepLocalizationHandler = { step in
    switch step {
    case .pinchToZoom:
        return NSLocalizedString("Pinch to zoom", comment: "WannaSDK: onboarding")
    }
}

WannaBags.Flow(config: config, modelId: "PUT_YOUR_MODEL_ID_HERE")
    .withUISettings(uiSettings)
```

| Step     |    Description    |
| -----|-------|
| `.pinchToZoom` | "Pinch to zoom" onboarding step |
<!-- | `.doubleTapToResetCamera` | "Double tap to reset camera" onboarding step | -->


<!--

### Point of interest (POI)

You can accompany every point of interest available in the model with some text to be displayed in UI. Each model can contain up to 3 POIs, so you can specify a text label for each of them. If you try to pass more text labels than the number of available POIs for the corresponding model, the 3D Viewer will display only the number of labels that correspond to POIs.

```swift
// Localized texts
let poiText = [
    nil, // means no text should be displayed for 1st POI
    NSLocalizedString("A removable top handle enables hand carry.", comment: "WannaSDK: 2nd POI text"),
    NSLocalizedString("Last POI Text sample.", comment: "WannaSDK: 3nd POI text"),
]

WannaBags.Flow(config: config, modelId: "PUT_YOUR_MODEL_ID_HERE")
    .withPOITextHandler { cameraIndex in

        // POI text for camera at index `cameraIndex`
        poiText[cameraIndex]
    }

// OR:

var uiSettings = WannaBags.UISettings()
uiSettings.poi.textHandler = {

}
``` -->
