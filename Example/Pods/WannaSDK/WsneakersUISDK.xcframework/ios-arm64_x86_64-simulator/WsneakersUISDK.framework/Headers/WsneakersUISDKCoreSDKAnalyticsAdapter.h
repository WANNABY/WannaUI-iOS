// WANNA SDK
// Copyright © 2021 WANNABY Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CoreSDKAnalyticsBackwardCompatibility;

@interface WsneakersUISDKCoreSDKAnalyticsAdapter : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithTracker:(id<CoreSDKAnalyticsBackwardCompatibility>)tracker;

@end

NS_ASSUME_NONNULL_END
