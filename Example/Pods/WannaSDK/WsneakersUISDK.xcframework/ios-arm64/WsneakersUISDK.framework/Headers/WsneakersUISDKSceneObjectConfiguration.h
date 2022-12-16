//
// WANNA SDK
// Copyright © 2022 WANNABY Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <WsneakersUISDK/WsneakersUISDKCameraPosition.h>
#import <WsneakersUISDK/WsneakersUISDKPoint.h>

NS_ASSUME_NONNULL_BEGIN

/**
Camera configuration.
*/
@interface WsneakersUISDKCameraConfiguration : NSObject
/**
Camera position.
*/
@property (strong, nonatomic) WsneakersUISDKCameraPosition* position;
/**
Camera POI.
*/
@property (strong, nonatomic) WsneakersUISDKPoint* poi;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithPosition:(WsneakersUISDKCameraPosition*)position poi:(WsneakersUISDKPoint*)poi;

@end

/**
Scene object configuration.
*/
@interface WsneakersUISDKSceneObjectConfiguration : NSObject
/**
Object length.
*/
@property (nonatomic) float objectLength;
/**
Minimum camera scale.
*/
@property (nonatomic) float minScale;
/**
Maximum camera scale.
*/
@property (nonatomic) float maxScale;
/**
Camera configuration for dimensions view,
*/
@property (strong, nonatomic) WsneakersUISDKCameraConfiguration* dimensionsViewCamera;
/**
Fallback camera configuration if no camera nodes are avaliable.
*/
@property (strong, nonatomic) WsneakersUISDKCameraConfiguration* fallbackCamera;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithObjectLength:(float)objectLength
                            minScale:(float)minScale
                            maxScale:(float)maxScale
                dimensionsViewCamera:(WsneakersUISDKCameraConfiguration*)dimensionsViewCamera
                      fallbackCamera:(WsneakersUISDKCameraConfiguration*)fallbackCamera;

@end

NS_ASSUME_NONNULL_END
