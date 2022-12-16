//
// WANNA SDK
// Copyright © 2019 WANNABY Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/**
The information about a 3D model.
*/
@interface WsneakersUISDKModelInfo : NSObject
/**
The 3D model identifier.
*/
@property (strong, nonatomic, readonly) NSString* renderModelID;
/**
The date of last change to the 3D model.
*/
@property (strong, nonatomic, readonly) NSDate* updatedDate;
/**
The type of the 3D model, for example `sneaker` or `watch`.
*/
@property (strong, nonatomic, readonly) NSString* renderModelType;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
