//
// WANNA SDK
// Copyright © 2019 WANNABY Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WsneakersUISDK/WsneakersUISDKDownloadTask.h>
#import <WsneakersUISDK/WsneakersUISDKModelInfo.h>
#import <WsneakersUISDK/WsneakersUISDKRenderModel.h>
#import <WsneakersUISDK/WsneakersUISDKRenderModelStorage.h>

NS_ASSUME_NONNULL_BEGIN

/**
Model storage and management.

Provides methods for downloading and storing the 3D models.
All operations perform asynchronously in the internal concurrent queue.
*/
@interface WsneakersUISDKLayout1RenderModelStorage : WsneakersUISDKRenderModelStorage

- (instancetype)init NS_UNAVAILABLE;

+ (nullable instancetype)createStorageWithConfig:(NSString*)config
                                       cacheSize:(size_t)cacheSize
                                           error:(NSError* __autoreleasing*)error;

@end

NS_ASSUME_NONNULL_END
