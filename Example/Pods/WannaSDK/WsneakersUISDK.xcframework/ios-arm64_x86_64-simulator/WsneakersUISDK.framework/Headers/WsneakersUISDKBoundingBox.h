//
// WANNA SDK
// Copyright © 2022 WANNABY Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <WsneakersUISDK/WsneakersUISDKPoint.h>

NS_ASSUME_NONNULL_BEGIN

/**
Bounding box.
*/
@interface WsneakersUISDKBoundingBox : NSObject
/**
Bounding box min point
*/
@property (strong, nonatomic) WsneakersUISDKPoint* min;
/**
Bounding box max point
*/
@property (strong, nonatomic) WsneakersUISDKPoint* max;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithMin:(WsneakersUISDKPoint*)min max:(WsneakersUISDKPoint*)max;

@end

NS_ASSUME_NONNULL_END
