//
// WANNA SDK
// Copyright © 2021 WANNABY Inc. All rights reserved.
//

#import "WsneakersUISDKViewerNode.h"
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import <WsneakersUISDK/WsneakersUISDKAnimation.h>
#import <WsneakersUISDK/WsneakersUISDKBoundingBox.h>
#import <WsneakersUISDK/WsneakersUISDKCameraPosition.h>
#import <WsneakersUISDK/WsneakersUISDKPoint.h>
#import <WsneakersUISDK/WsneakersUISDKSceneNode.h>
#import <WsneakersUISDK/WsneakersUISDKSceneObjectConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^FrameHandler)(id<MTLTexture> _Nullable, NSInteger);
typedef BOOL (^ProgressHandler)(float progress);
typedef void (^LoadSessionCompletion)(BOOL isSuccess, NSError* _Nullable error);
typedef void (^SetModelCompletion)(BOOL isSuccess, NSError* _Nullable error);
typedef void (^PresentObjectCompletion)(BOOL isSuccess, NSError* _Nullable error);
typedef void (^GetNodesCompletion)(NSArray<WsneakersUISDKSceneNode*>* _Nullable);
typedef void (^GetBoundingBoxCompletion)(const WsneakersUISDKBoundingBox* _Nullable);
typedef void (^GetSceneObjectConfigurationCompletion)(const WsneakersUISDKSceneObjectConfiguration* _Nullable);
typedef void (^GetCameraPositionCompletion)(const WsneakersUISDKCameraPosition* _Nullable poi);
typedef void (^GetCameraPOICompletion)(const WsneakersUISDKPoint* _Nullable poi);
typedef void (^OnCameraChangeCompletion)(
    const WsneakersUISDKCameraPosition* _Nullable position, const WsneakersUISDKPoint* _Nullable poi);
typedef void (^MakeAnimationCompletion)(const WsneakersUISDKAnimation* _Nullable animation);

typedef NSArray<WsneakersUISDKCameraPosition*>* _Nonnull (^MakeBezierControlPointsFunction)(
    const WsneakersUISDKCameraPosition* _Nonnull start_point, const WsneakersUISDKCameraPosition* _Nonnull end_point);

typedef uint32_t WsneakersUISDKObjectIndex;

extern WsneakersUISDKObjectIndex const kWsneakersUISDKLeftSneakerObject;
extern WsneakersUISDKObjectIndex const kWsneakersUISDKRightSneakerObject;

@interface WsneakersUISDKViewerSessionAdapter : NSObject

@property (nonatomic, copy, nullable) FrameHandler frameHandler;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithClientConfig:(NSString*)clientConfig progressHandler:(nullable ProgressHandler)progressHandler;

- (void)loadSessionWithCompletion:(nullable LoadSessionCompletion)completion;
- (void)setViewportHeight:(unsigned int)height width:(unsigned int)width;
- (void)presentObjectAtIndex:(WsneakersUISDKObjectIndex)objectIdx
                  completion:(nullable PresentObjectCompletion)completion;
- (void)getNodesForObjectAtIndex:(WsneakersUISDKObjectIndex)objectIdx completion:(GetNodesCompletion)completion;
- (void)getBoundingBoxForObjectAtIndex:(WsneakersUISDKObjectIndex)objectIdx
                            completion:(GetBoundingBoxCompletion)completion;
- (void)getConfigurationForObjectAtIndex:(WsneakersUISDKObjectIndex)objectIdx
                              completion:(GetSceneObjectConfigurationCompletion)completion;
- (void)setConfiguration:(WsneakersUISDKSceneObjectConfiguration*)configuration
        forObjectAtIndex:(WsneakersUISDKObjectIndex)objectIdx;
- (void)setNode:(WsneakersUISDKSceneNodeRef)node
    forObjectAtIndex:(WsneakersUISDKObjectIndex)objectIdx
             visible:(bool)visible
     withDescendants:(bool)withDescendants;
- (void)setCameraFromNode:(WsneakersUISDKSceneNodeRef)node forObjectAtIndex:(WsneakersUISDKObjectIndex)objectIdx;
- (void)rotateTargetWithYaw:(float)yaw pitch:(float)pitch;
- (void)setScale:(float)scale;
- (void)makeFadeOutAnimationForNode:(WsneakersUISDKSceneNodeRef)node
                   forObjectAtIndex:(WsneakersUISDKObjectIndex)objectIdx
                         completion:(MakeAnimationCompletion)completion;
- (void)makeBezierCurveCameraMoveAnimationForNode:(WsneakersUISDKSceneNodeRef)node
                                 forObjectAtIndex:(WsneakersUISDKObjectIndex)objectIdx
                        makeControlPointsFunction:(nullable MakeBezierControlPointsFunction)makeControlPointsFunction
                                       completion:(MakeAnimationCompletion)completion;
- (void)makeBezierCurveCameraMoveAnimationForPos:(const WsneakersUISDKCameraPosition*)pos
                                             poi:(const WsneakersUISDKPoint*)poi
                                forObjectAtIndex:(WsneakersUISDKObjectIndex)objectIdx
                       makeControlPointsFunction:(nullable MakeBezierControlPointsFunction)makeControlPointsFunction
                                      completion:(MakeAnimationCompletion)completion;
- (void)getCameraPosition:(GetCameraPositionCompletion)completion;
- (void)setCameraPosition:(WsneakersUISDKCameraPosition*)position;
- (void)getCameraPOI:(GetCameraPOICompletion)completion;
- (void)setCameraPOI:(WsneakersUISDKPoint*)poi;
- (void)setCameraChangeCompletion:(nullable OnCameraChangeCompletion)completion;
- (void)setModel:(id _Nonnull)model completion:(nullable SetModelCompletion)completion;
- (void)pushFrameWithWidth:(int)width height:(int)height index:(int)index;

@end

NS_ASSUME_NONNULL_END
