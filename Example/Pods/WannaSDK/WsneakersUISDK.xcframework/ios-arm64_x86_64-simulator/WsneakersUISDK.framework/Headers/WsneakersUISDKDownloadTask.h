//
// WANNA SDK
// Copyright © 2019 WANNABY Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
The download manager for 3D models.

An object of this type is returned by the methods of
``WsneakersUISDKRenderModelStorage``. Use it to interrupt download if necessary.
*/
@interface WsneakersUISDKDownloadTask : NSObject

/**
Cancels current download.
*/
- (void)cancel;

@end

NS_ASSUME_NONNULL_END
