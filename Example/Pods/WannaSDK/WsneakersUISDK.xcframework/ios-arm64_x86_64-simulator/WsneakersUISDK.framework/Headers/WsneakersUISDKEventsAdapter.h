//
// WANNA SDK
// Copyright © 2021 WANNABY Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WsneakersUISDKEventsAdapter : NSObject

+ (void)track3DViewerMeasureFps:(NSString*)modelID fps:(float)fps;

+ (void)track3DViewerError:(NSString*)error;

@end

NS_ASSUME_NONNULL_END
