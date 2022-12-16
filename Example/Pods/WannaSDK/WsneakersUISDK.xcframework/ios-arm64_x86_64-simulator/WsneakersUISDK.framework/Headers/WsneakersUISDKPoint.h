//
// WANNA SDK
// Copyright © 2022 WANNABY Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
3D scene point.
*/
@interface WsneakersUISDKPoint : NSObject
/**
Coordinate by X-axis.
*/
@property (nonatomic) float x;
/**
Coordinate by Y-axis.
*/
@property (nonatomic) float y;
/**
Coordinate by Z-axis.
*/
@property (nonatomic) float z;

- (instancetype)init;

- (instancetype)initWithX:(float)x y:(float)y z:(float)z;

@end

NS_ASSUME_NONNULL_END
