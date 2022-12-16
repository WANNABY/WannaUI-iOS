//
// WANNA SDK
// Copyright © 2019 WANNABY Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WsneakersUISDK/WsneakersUISDKSession.h>

NS_ASSUME_NONNULL_BEGIN
/**
The view that will render virtual try-on frames.
*/
@interface WsneakersUISDKView : UIView
/**
The mask that controls view orientation.
Default value is `UIInterfaceOrientationMaskPortrait`, which we recommend.
*/
@property (nonatomic, assign) UIInterfaceOrientationMask supportedOrientationMask;

- (instancetype)init;

- (instancetype)initWithFrame:(CGRect)frame;

- (instancetype)initWithCoder:(NSCoder*)aDecoder;

@end

NS_ASSUME_NONNULL_END
