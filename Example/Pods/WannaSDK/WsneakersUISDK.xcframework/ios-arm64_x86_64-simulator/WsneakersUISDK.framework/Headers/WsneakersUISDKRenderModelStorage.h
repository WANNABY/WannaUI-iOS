//
// WANNA SDK
// Copyright © 2019 WANNABY Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WsneakersUISDK/WsneakersUISDKDownloadTask.h>
#import <WsneakersUISDK/WsneakersUISDKModelInfo.h>
#import <WsneakersUISDK/WsneakersUISDKRenderModel.h>

/**
The errors that may occur when working with model storage.
*/
typedef NS_ENUM(NSUInteger, WsneakersUISDKRenderModelStorageError) {
    WsneakersUISDKRenderModelStorageErrorInternal = 600,
    WsneakersUISDKRenderModelStorageErrorNoConfig = 601,
    WsneakersUISDKRenderModelStorageErrorConfigCorrupted = 602,
    WsneakersUISDKRenderModelStorageErrorNetwork = 603,
    WsneakersUISDKRenderModelStorageErrorServer = 604,
    WsneakersUISDKRenderModelStorageErrorAccessDenied = 605,
    WsneakersUISDKRenderModelStorageErrorProtocol = 606,
    WsneakersUISDKRenderModelStorageErrorInvalidParameter = 607,
    WsneakersUISDKRenderModelStorageErrorConnectivity = 608,
    WsneakersUISDKRenderModelStorageErrorUnsupported = 609,
    WsneakersUISDKRenderModelStorageErrorCache = 610,
    WsneakersUISDKRenderModelStorageErrorNetworkConnection = 611,
    WsneakersUISDKRenderModelStorageErrorNetworkTimeout = 612,
    WsneakersUISDKRenderModelStorageErrorBadLicense = 613,
    WsneakersUISDKRenderModelStorageErrorLicenseExpired = 614,
    WsneakersUISDKRenderModelStorageErrorNoCompletionCallback = 615,
    WsneakersUISDKRenderModelStorageErrorDeprecated = 621
};

NS_ASSUME_NONNULL_BEGIN

extern NSErrorDomain const kWUISDKRenderModelErrorDomain;

typedef void (^ProgressCallback)(WsneakersUISDKDownloadTask* task, float progress);

typedef void (^LoadModelsCompletion)(
    NSArray<WsneakersUISDKModelInfo*>* _Nullable renderModels, NSError* _Nullable error);

/**
Model storage and management.

Provides methods for downloading and storing the 3D models.
All operations perform asynchronously in the internal concurrent queue.
*/
@interface WsneakersUISDKRenderModelStorage : NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
Initializes a new storage object. Runs synchronously.
@param[in] config the license string that authorizes your use of WANNA SDK
@param[in] cacheSize the storage size
@param[out] error stores the error description on failure
@return a newly initialized storage object or nil in case of failure
*/
+ (nullable instancetype)createStorageWithConfig:(NSString*)config
                                       cacheSize:(size_t)cacheSize
                                           error:(NSError* __autoreleasing*)error;

/**
Loads the list of available models.
- Warning: This method is intended for internal use only.
*/
- (void)loadModelsWithCompletion:(LoadModelsCompletion)completion;

/**
Downloads the specified 3D model from cloud if it isn't already in cache. Runs asynchronously.
Once the model is loaded, it's immediately assigned to the try-on session.
@param[in] renderModelID the unique identifier of the 3D model
@param[out] progress a block that receives current progress from 0.0 to 1.0
@param[out] completion a block that receives either the 3D model or the error object on failure
@warning completion block will never get called for a cancelled task
@return the download task that can be used to cancel the download
*/
- (WsneakersUISDKDownloadTask*)getRenderModelWithID:(NSString*)renderModelID
                                           progress:(nullable ProgressCallback)progress
                                         completion:(void (^)(WsneakersUISDKRenderModel* _Nullable renderModel,
                                                        NSError* _Nullable error))completion;

/**
Downloads the 3D model from the given URL if it isn't already in cache. Runs asynchronously.
On completion, you can call ``changeRenderModel`` to start try-on with this model.
@param[in] url the link to where the model is stored
@param[out] progress a block that receives current progress from 0.0 to 1.0
@param[out] completion a block that receives either the 3D model or the error object on failure
@warning completion block will never get called for a cancelled task
@return the download task that can be used to cancel the download
*/
- (WsneakersUISDKDownloadTask*)getRenderModelWithURL:(NSURL*)url
                                            progress:(nullable ProgressCallback)progress
                                          completion:(void (^)(WsneakersUISDKRenderModel* _Nullable renderModel,
                                                         NSError* _Nullable error))completion;

/**
Downloads the specified 3D model from cloud if it isn't already in cache. Doesn't load the model into memory.
Runs asynchronously.
@param[in] renderModelID the unique identifier of the 3D model
@param[out] progress a block that receives current progress from 0.0 to 1.0
@param[out] completion a block that receives either the 3D model or the error object on failure
@warning completion block will never get called for a cancelled task
@returns the download task that can be used to cancel the download
*/
- (WsneakersUISDKDownloadTask*)preloadRenderModelWithID:(NSString*)renderModelID
                                               progress:(nullable ProgressCallback)progress
                                             completion:(void (^)(BOOL success, NSError* _Nullable error))completion;

/**
Removes all 3D models and clears the storage.
*/
- (void)clearCache;

- (nullable WsneakersUISDKRenderModel*)getLocalRenderModelWithID:(NSString*)renderModelID;

@end

NS_ASSUME_NONNULL_END
