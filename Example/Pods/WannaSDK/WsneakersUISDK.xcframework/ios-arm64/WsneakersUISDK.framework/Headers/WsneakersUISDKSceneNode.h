//
// WANNA SDK
// Copyright © 2022 WANNABY Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WsneakersUISDK/WsneakersUISDKBoundingBox.h>

NS_ASSUME_NONNULL_BEGIN

typedef void* WsneakersUISDKSceneNodeRef;

/**
Scene node types.
*/
typedef NS_ENUM(NSUInteger, WsneakersUISDKSceneNodeType) {
    WsneakersUISDKSceneNodeTypeUnknown,

    WsneakersUISDKSceneNodeTypeMain,
    WsneakersUISDKSceneNodeTypePlaneAO,
    WsneakersUISDKSceneNodeTypeStrapLong,
    WsneakersUISDKSceneNodeTypePlaneAOStrap,
    WsneakersUISDKSceneNodeTypeDimensionCm,
    WsneakersUISDKSceneNodeTypeDimensionInch,

    WsneakersUISDKSceneNodeTypeCamera
};

/**
Scene node representation.
*/
@interface WsneakersUISDKSceneNode : NSObject
/**
Identifier of the node.
*/
@property (nonatomic, readonly) uint32_t nodeID;
/**
Name of the node.
*/
@property (strong, nonatomic, readonly) NSString* name;
/**
True if node contains camera params.
*/
@property (nonatomic, readonly) WsneakersUISDKSceneNodeType type;
/**
Node bounding box.
*/
@property (strong, nonatomic, readonly) WsneakersUISDKBoundingBox* boundingBox;
/**
Node ref.
*/
@property (nonatomic, readonly) WsneakersUISDKSceneNodeRef ref;
/**
Node children.
*/
@property (strong, nonatomic, readonly) NSArray<WsneakersUISDKSceneNode*>* children;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
