//
// WANNA SDK
// Copyright © 2021 WANNABY Inc. All rights reserved.
//

#import "WsneakersUISDKViewerSessionAdapter.h"
#import <WsneakersUISDK/WsneakersUISDK.h>

NS_ASSUME_NONNULL_BEGIN

@interface WsneakersUISDKViewerSessionAdapter (Pub)

- (void)setNode:(WsneakersUISDKSceneNodeRef)node visible:(bool)visible;

- (void)makeBezierCurveCameraMoveAnimationForNode:(WsneakersUISDKSceneNodeRef)node
                                       completion:(MakeAnimationCompletion)completion;

- (void)makeBezierCurveCameraMoveAnimationForPos:(const WsneakersUISDKCameraPosition*)pos
                                             poi:(const WsneakersUISDKPoint*)poi
                                forObjectAtIndex:(WsneakersUISDKObjectIndex)objectIdx
                                      completion:(MakeAnimationCompletion)completion;

@end

NS_ASSUME_NONNULL_END
