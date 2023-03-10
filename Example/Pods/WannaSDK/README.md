# Get started with WANNA SDK

WANNA SDK enhances your iOS app with virtual try-on capabilities for shoes and watches. With this feature, your users will be able to see in real time how the selected product looks on them, just by pointing their smartphone camera at their feet or wrist.

This tutorial walks you through the simplest try-on use case: load the library, start the camera, show the virtual try-on and unload everything when done. We won't be paying much attention to error handling or more elaborate use scenarios.

Check out also the code sample that implements this use case. See the **ios/Swift** folder in the distribution.

In addition, WANNA SDK gives you a built-in 3D viewer for sneakers. It displays a sneaker 3D model in an interactive window, where the user can rotate the view to explore the tiniest details of the sneaker's appearance.

<!-- TOC -->

- [Prerequisites](#prerequisites)
- [Installation](#installation)
	- [CocoaPod](#cocoapod)
	- [Frameworks](#frameworks)
- [Step-by-step](#step-by-step)
	- [Write your part of the code](#write-your-part-of-the-code)
	- [Implement virtual try-on](#implement-virtual-try-on)
	- [Implement a 3D viewer](#implement-a-3d-viewer)
- [Sample](#sample)
- [Distribution](#distribution)
- [System requirements](#system-requirements)

<!-- /TOC -->

## Prerequisites

To work with WANNA SDK, you will need:

* **WANNA distribution**. <br>
Use either the frameworks or the CocoaPod<!-- TODO: insert link!-->.
* the **license key** that authorizes WANNA SDK use. <br>
Contact our sales representative at [account@wanna.fashion](mailto:account@wanna.fashion) to get one.
* **3D models** of your products. <br>
A model ID should be an alphanumeric string, with hyphens and underscores but no other special characters. Otherwise, set the IDs in any way convenient to you: the ID can be an internal product code or a vendor ID, as long as it is unique for each model. The models will be stored in a content delivery network (CDN) to ensure availability across different regions. Note that each color should have its own model???WANNA SDK can't touch up the colors on the fly.

## Installation

Add WANNA SDK to your project either as a CocoaPod or by embedding the frameworks in your Xcode project.

### CocoaPod

Create a Podfile if you haven't yet:

```
$ cd <your-project-directory>
$ pod init
```

Add the WannaSDK pod to your Podfile:

```
platform :ios, '10.0'

target 'MyApp' do
  pod 'WannaSDK'
end
```

Install the pod:

```
$ pod install
```

### Frameworks

1. Add **WsneakersCoreSDK.xcframework** and **WsneakersUISDK.xcframework** to your project in Xcode.
2. Embed these frameworks in the main bundle of your project.

## Step-by-step

### Write your part of the code

WANNA SDK will only provide the try-on or 3D viewer experience. Some things you will have to implement for yourself:

* the launch button on the product page
* any overlays for the camera window, tips for the user, etc.

### Implement virtual try-on

**Note:** Add the `NSCameraUsageDescription` key to **Info.plist**, so that your app can use the camera.

In ViewController, add a new **UIView** component using Interface Builder and select `WsneakersUISDKView` custom class for it.

Write the code for working with the SDK in **WsneakersViewController.swift**:

1. Initialize the try-on session.<br>
For sneakers, call the `createSession` method:<br>
`let session = try WsneakersUISDKSession.createSession(withConfig: clientConfig, withBorderCrop: 0.0, progress: { progress in
                return true
            })`<br>
For watches, call the `createWatchSession` method:<br>
`let session = try WsneakersUISDKSession.createWatchSession(withConfig: clientConfig, withBorderCrop: 0.0, progress: { progress in
                return true
            })`<br>
Note that this method requires the license key (`clientConfig`) that authorizes your use of WANNA SDK.<br>
If needed, crop the try-on view with a different value of `borderCrop`, so that the relevant area is zoomed in. You may want to show a progress indicator in the progress block, because the initialization, with loading all the resources, will take some time.<br>
The good time to initialize is when the user goes to a screen that offers virtual try-on and you expect them to use it. Note that initialization will take up some processing resources and download traffic on the user's device. To prevent overuse of these resources, avoid initializing too early.
2. Implement a `WsneakersUISDKSessionDelegate` protocol and assign it to the `delegate` property of the session object. The `hasVisibleFeet` parameter will tell you if we've found the object on which to try on your product - feet or wrist - in the camera view. This can be useful if you'd like to show a tip to the user when the camera isn't pointed in the right direction.
3. Connect the view you created to the session via an outlet:<br>
`@IBOutlet var tryonView : WsneakersUISDKView!
wsneakersSession.wsneakersUISDKView = wsneakersView`
4. When the session has loaded and everything is ready, `startSession` to begin work.
5. To show the try-on screen, call the `startDrawing` method each time the try-on becomes active.
6. Make sure your app handles the "idle" time with no user input so that the screen isn't dimmed or turned off during virtual try-on:<br>
`UIApplication.shared.isIdleTimerDisabled = true`<br>
Don't forget to reset this setting when the try-on session is completed. See the recommendations at https://developer.apple.com/documentation/uikit/uiapplication/1623070-isidletimerdisabled
7. Create the storage object that will load and manage models. Use the `createStorage` method, passing in the client configuration string. This is also where you can limit cache size for model storage, we suggest about 200 MB.<br>
`let storage = try! WsneakersUISDKRenderModelStorage.createStorage(withConfig: clientConfig, withCacheSize: 1024*1024*200)`<br>
Once the user has tried on a model, it will be kept in cache until you destroy the session. If the stored models overflow the cache, WANNA SDK will delete the model that was unused the longest. If you need to remove the stored models, call `clearCache`.
8. Call the `getRenderModel` method of the storage object, passing the model ID as input. At this point we will download the model, which may take some time. If the user has tried this model on in this session and it's already in cache, that will save time.<br>
The completion block will contain a `WsneakersUISDKRenderModel` object representing the model.
9. Pass the model object into the `changeRenderModel` method of the session object. WANNA SDK will render the product on the user's feet, or wrist, once they are in the frame.
10. Whenever the user goes out of the virtual try-on, `stopDrawing` to turn off the camera view and the model rendering. If they then come back, `startDrawing` again. You might also want to `removeRenderModel` from the session, so that the old model won't be showing while the new one isn't ready yet.
11. When the user is done with their session, `stopDrawing` and `stopSession` to clear the resources. Note that the 3D models storage is kept even after exiting the app, and the stored models will be available on the next run.

### Implement a 3D viewer

**Note:** Only portrait screen orientation is supported for 3D viewer.

1. Create an instance of `WsneakersUISDKViewer3D` class and add it to view. Or, if you prefer to do it via GUI, add a `WsneakersUISDKViewer3D` object to your storyboard and link it to **IBOutlet**.
2. Set up the instance by calling `setup` method:<br>
`setup( clientConfig: "WSNEAKERS_CLIENT_CONFIG_CHANGE_HERE",
        onProgress: ((Float) -> Bool)?,
        onSuccess: (() -> Void)?,
        onError: ((Error) -> Void)?) `<br>
Note that this method requires the license key (`clientConfig`) that authorizes your use of WANNA SDK. Handle the set up outcome using the `onSuccess` and `onError` blocks.
3. Create the storage object that will load and manage models. Use the `createStorage` method, providing the client configuration key. This is also where you can limit cache size for model storage, we suggest about 200 MB.<br>
`let storage = try! WsneakersUISDKRenderModelStorage.createStorage(withConfig: "WSNEAKERS_CLIENT_CONFIG_CHANGE_HERE", withCacheSize: 1024*1024*200)`<br>
Once a model is loaded, it will be kept in cache until you destroy the session. If the stored models overflow the cache, WANNA SDK will delete the model that was unused the longest. If you need to remove the stored models, call `clearCache`.
4. Call the `getRenderModel` method of the storage object, passing the model ID as input. At this point we will download the model, which may take some time. If the user has looked at this model already and it's in cache, that will save time.<br>
The completion block will contain a `WsneakersUISDKRenderModel` object representing the model.<br>
**Note:** Reuse the objects for storage and models, if you have already created and loaded them for the [try-on session](#implement-virtual-try-on).
6. Pass the model object into the `setModel` method of the `WsneakersUISDKViewer3D` object.
7. To start rendering frames, call the `start()` method.
8. If the model includes several objects, for example left and right for sneakers, you can switch between them with the `presentObject(atIndex: )` method.
9. Once the user finishes with the 3D viewer, call `stop()` to stop rendering.

## Sample

Our distribution includes a simple code sample in Swift: see **ios/Swift** folder in the distribution. Use it to test our SDK capabilities or as a starting point to develop your own app.

Before building and running the sample:

1. Enter your license key in **WANNASDKDefaults.swift**:
```
static let clientConfig = "WSNEAKERS_CLIENT_CONFIG_CHANGE_HERE"
```
2. Assign a development team to the sample Xcode project, to ensure it's signed correctly. Go to the **Signing & Capabilities** tab in Xcode and choose the appropriate value in the **Team** dropdown list.

## Distribution

* **ios** folder with code samples in Swift and Objective-C for the basic virtual try-on scenario.
* **WannaSDK** folder with the library files required if you are using WANNA SDK. Redistribute these with your application.
* **readme** folder with this file and other product documentation.

## System requirements

* iOS version: 12.0 or later
* Supported devices: iPhone SE/6s and later
* Memory requirements:
	* Footprint (zipped), contributes to the downloadable size of your app:
		* iOS 12.2 and later: 3.4 MB for library files
		* iOS 12.0 - 12.1.4: 5.9 MB for library files
	* Footprint (unzipped), contributes to the space your app takes up when installed:
		* iOS 12.2 and later: 8.6 MB for library files
		* iOS 12.0 - 12.1.4: 16.3 MB for library files
		* 25 MB cache for neural networks and auxiliary files
		* the cache for 3D model storage can be set via API
	* RAM: up to 600 MB, depending on the size and quality of the 3D model
