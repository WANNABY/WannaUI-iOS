// WANNA SDK
// Copyright © 2021 WANNABY Inc. All rights reserved.

#import "WsneakersUISDKLayout2RenderModel.h"

NS_ASSUME_NONNULL_BEGIN

@class RenderModel;

API_AVAILABLE(ios(13.0))
@interface WsneakersUISDKLayout2RenderModel ()

@property (strong, nonatomic) RenderModel* renderModel;
@property (strong, nonatomic, readonly) NSURL* modelRmdescURL;
@property (copy, nonatomic, readonly) NSDictionary<NSString*, NSURL*>* dataPacks;

@property (copy, nonatomic, readonly) NSString* renderModelID;
@property (assign, nonatomic, readonly) BOOL cancelable;

- (instancetype)initWithRenderModel:(RenderModel*)renderModel API_AVAILABLE(ios(13.0));

@end

NS_ASSUME_NONNULL_END
