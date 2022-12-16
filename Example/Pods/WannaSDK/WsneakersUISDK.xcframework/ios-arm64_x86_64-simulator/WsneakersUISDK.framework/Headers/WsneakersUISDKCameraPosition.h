//
// WANNA SDK
// Copyright © 2022 WANNABY Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
Camera position.
*/
@interface WsneakersUISDKCameraPosition : NSObject
/**
Rotation about Y axis.
*/
@property (nonatomic) float yaw;
/**
Rotation about X axis.
*/
@property (nonatomic) float pitch;
/**
Camera scale.
*/
@property (nonatomic) float scale;

- (instancetype)init;

- (instancetype)initWithYaw:(float)yaw pitch:(float)pitch scale:(float)scale;

@end

NS_ASSUME_NONNULL_END
