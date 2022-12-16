// WANNA SDK
// Copyright © 2022 WANNABY Inc. All rights reserved.

#import "WsneakersCoreSDK_headers.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WsneakersUISDKViewerContainer : NSObject

@property (nonatomic, assign) WsneakersCoreSDKSessionRef sessionRef;
@property (nonatomic, assign) WsneakersCoreSDKSceneControllerRef sceneControllerRef;
@property (nonatomic, assign, nullable) WsneakersCoreSDKSceneControllerRef libraryRef;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithSessionRef:(WsneakersCoreSDKSessionRef)sessionRef
                sceneControllerRef:(WsneakersCoreSDKSessionRef)sceneControllerRef
                        libraryRef:(nullable WsneakersCoreSDKLibraryRef)libraryRef;

@end
NS_ASSUME_NONNULL_END
