// WANNA SDK
// Copyright © 2021 WANNABY Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WsneakersUISDKObjcUnzipAdapter : NSObject

+ (BOOL)unzipFileAtPath:(NSString*)path toDestination:(NSString*)destination;

@end

NS_ASSUME_NONNULL_END
