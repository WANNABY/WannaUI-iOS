//
// WANNA SDK
// Copyright © 2019 WANNABY Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
The 3D model and its resources.

Note that the model should never be created manually.
It can only be obtained from ``WsneakersUISDKRenderModelStorage``.
*/

NS_ASSUME_NONNULL_BEGIN

@interface WsneakersUISDKRenderModel : NSObject

@property (nonatomic, strong, nullable, readonly) NSString* renderModelID;
@property (copy, nonatomic, readonly) NSDictionary<NSString*, NSURL*>* dataPacks;

- (instancetype)init NS_UNAVAILABLE;

// Not for public. Internal use only.
+ (nullable __kindof WsneakersUISDKRenderModel*)createWithRenderModelID:(NSString*)renderModelID
                                                              rmdescURL:(NSURL*)rmdescURL
                                                              dataPacks:(NSDictionary<NSString*, NSURL*>*)dataPacks
                                                                 cancel:(void (^)(void))cancel API_AVAILABLE(ios(13.0));

+ (nullable WsneakersUISDKRenderModel*)createWithContentOfFile:(NSString*)filePath;

+ (nullable WsneakersUISDKRenderModel*)createEmpty;

@end

NS_ASSUME_NONNULL_END
