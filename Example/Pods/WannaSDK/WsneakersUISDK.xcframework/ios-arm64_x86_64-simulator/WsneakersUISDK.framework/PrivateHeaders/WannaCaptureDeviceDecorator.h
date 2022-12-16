// WANNA SDK
// Copyright © 2022 WANNABY Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCaptureDevice;

@interface WannaCaptureDeviceDecorator : NSProxy

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithCaptureDevice:(AVCaptureDevice*)captureDevice;

@end

NS_ASSUME_NONNULL_END
