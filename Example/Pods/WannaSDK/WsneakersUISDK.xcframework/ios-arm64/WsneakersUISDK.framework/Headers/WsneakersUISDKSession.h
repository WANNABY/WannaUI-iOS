//
// WANNA SDK
// Copyright © 2019 WANNABY Inc. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <WsneakersUISDK/WsneakersUISDKRenderModel.h>
#import <WsneakersUISDK/WsneakersUISDKRenderModelStorage.h>
#import <WsneakersUISDK/WsneakersUISDKSessionDelegate.h>
#import <WsneakersUISDK/WsneakersUISDKView.h>

/**
The errors that may occur during a virtual try-on session.
*/
typedef NS_ENUM(NSUInteger, WsneakersUISDKSessionError) {
    WsneakersUISDKSessionErrorInternal = 30000,
    WsneakersUISDKSessionErrorNoConfig = 30001,
    WsneakersUISDKSessionErrorConfigCorrupted = 30002,
    WsneakersUISDKSessionErrorNetwork = 30003,
    WsneakersUISDKSessionErrorServer = 30004,
    WsneakersUISDKSessionErrorAccessDenied = 30005,
    WsneakersUISDKSessionErrorProtocol = 30006,
    WsneakersUISDKSessionErrorInvalidParameter = 300007,
    WsneakersUISDKSessionErrorConnectivity = 30008,
    WsneakersUISDKSessionErrorUnsupported = 30009,
    WsneakersUISDKSessionErrorCache = 30010,
    WsneakersUISDKSessionErrorNetworkConnection = 30011,
    WsneakersUISDKSessionErrorNetworkTimeout = 30012,
    WsneakersUISDKSessionErrorBadLicense = 30013,
    WsneakersUISDKSessionErrorLicenseExpired = 30014,
    WsneakersUISDKSessionErrorNoCompletionCallback = 30015,
    WsneakersUISDKSessionErrorDeprecated = 30021,
    WsneakersUISDKSessionErrorSetRenderModel = 30022,
    WsneakersUISDKSessionErrorCaptureOutput = 30023,
    WsneakersUISDKSessionErrorCaptureInput = 30024,
    WsneakersUISDKSessionErrorCaptureDeviceCreation = 30025,
    WsneakersUISDKSessionErrorCaptureSessionAddition = 30026,
    WsneakersUISDKSessionErrorUnableToProcessFrame = 30027,
    WsneakersUISDKSessionErrorUnableToHandleFrame = 30028,
    WsneakersUISDKSessionErrorNilImage = 30029,
    WsneakersUISDKSessionErrorPipelineInfo = 30030,
    WsneakersUISDKSessionErrorActiveSessionExists = 30031,
    WsneakersUISDKSessionErrorCancelled = 30032
};

@class WsneakersUISDKSession;
@class WsneakersUISDKView;

NS_ASSUME_NONNULL_BEGIN

@interface WsneakersUISDKSession : NSObject
/**
The view that the session manages. This property should be accessed only from the main thread.
*/
@property (weak, nonatomic, nullable) WsneakersUISDKView* wsneakersUISDKView;
/**
Delegate object that receives additional info.
*/
@property (weak, nonatomic, nullable) id<WsneakersUISDKSessionDelegate> delegate;

/**
Specifies what portion of the image should be removed from each side.

For example, 0.1 means 10%, i.e. remove 10% from the left, 10% from the right,
10% from the top and 10% from the bottom, so that a 1000x1000 image is reduced to 800x800.
Only values in [0, 0.5) range are valid.
*/
@property (nonatomic, assign, readonly) float borderCrop;

/**
The capture session preset.

For example, an `AVCaptureSessionPreset1280x720` preset is suitable for 1280x720 video output,
and `AVCaptureSessionPreset1920x1080` is suitable for 1920x1080 video output.
*/
@property (strong, nonatomic, readonly) AVCaptureSessionPreset preset;

/**
Checks if WANNA SDK can function on the current device.
*/
+ (BOOL)isDeviceSupported;

- (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
Creates a sneakers try-on session.

Runs synchronously from the calling queue.
The first call will require network connection and
will take some time to load all required resources.
If successful, the other calls may be performed without network connection.
@param[in] config the license string that authorizes your use of WANNA SDK
@param[in] borderCrop the percentage to remove from each side, same as in the ``borderCrop`` property
@param[out] progress a block that receives current progress from 0.0 to 1.0 and may return NO to cancel download
@param[out] error stores the error description on failure
@return a newly initialized session object or nil in case of failure
*/
+ (nullable WsneakersUISDKSession*)createSessionWithConfig:(NSString*)config
                                                borderCrop:(float)borderCrop
                                                  progress:(BOOL (^_Nullable)(float progress))progress
                                                     error:(NSError* __autoreleasing*)error;

/**
Creates a watch try-on session.

Runs synchronously from the calling queue.
The first call will require network connection and
will take some time to load all required resources.
If successful, the other calls may be performed without network connection.
@param[in] config the license string that authorizes your use of WANNA SDK
@param[in] borderCrop the percentage to remove from each side, same as in the ``borderCrop`` property
@param[out] progress a block that receives current progress from 0.0 to 1.0 and may return NO to cancel download
@param[out] error stores the error description on failure
@return a newly initialized session object or nil in case of failure
*/
+ (nullable WsneakersUISDKSession*)createWatchSessionWithConfig:(NSString*)config
                                                     borderCrop:(float)borderCrop
                                                       progress:(BOOL (^_Nullable)(float progress))progress
                                                          error:(NSError* __autoreleasing*)error;

/**
Runs synchronously from the calling queue.
Waits while previous session finish destroy process
@param[in] timeout timeout in seconds
@return true - no active session and you can create new; false - session not destroyed.
*/
+ (BOOL)waitForSessionDestroyWithTimeout:(NSTimeInterval)timeout;

/**
Returns camera permission status. Runs asynchronously.
@param[out] completion a block that receives camera's permission status: YES if granted, otherwise NO
*/
+ (void)checkCameraAccess:(void (^)(BOOL granted))completion;

/**
Camera permission status.
*/
+ (AVAuthorizationStatus)authorizationStatusForCamera;

/**
Starts the try-on session. Runs asynchronously. The video stream will not be rendered until ``startDrawing`` call.
*/
- (void)startSession;

/**
Stops the try-on session. Runs asynchronously.
@param[out] completion a block that receives nil on success or the error object on failure
*/
- (void)stopSession:(void (^_Nullable)(NSError* _Nullable error))completion;

/**
Checks if the drawing session is on. Runs synchronously.
*/
- (BOOL)isDrawing;

/**
Starts rendering the video stream. Runs asynchronously.
@param[out] completion a block which notifies your code when the first frame has been processed
*/
- (void)startDrawing:(void (^)(void))completion;

/**
Starts rendering the video stream. Runs asynchronously.

If a model has already been chosen and loaded it's rendered at once.
Otherwise, the raw stream from camera is shown until the model is ready.
*/
- (void)startDrawing;

/**
Stops rendering the video stream. Runs asynchronously.
*/
- (void)stopDrawing;

/**Assigns a render model to the session. Can be called without waiting for the model download to complete. Runs
asynchronously.
@param[in] renderModel the ID of the 3D model to try on
@param[out] completion a block that receives nil on success or the error object on failure
*/
- (void)changeRenderModel:(WsneakersUISDKRenderModel*)renderModel
               completion:(void (^)(NSError* _Nullable error))completion;

/**
Removes a render model from the session. Runs asynchronously.

With no model, the raw stream from camera will be shown until you ``stopDrawing``.
*/
- (void)removeRenderModel;
- (void)removeRenderModelWithCompletion:(nullable void (^)(NSError* _Nullable error))completion;

/**
Takes a snapshot of a video frame with the model rendered. Runs asynchronously.
@param[out] completion a block that receives either the image or the error object on failure
*/
- (void)captureStillPhoto:(void (^)(UIImage* _Nullable image, NSError* _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
