//
// WANNA SDK
// Copyright © 2021 WANNABY Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
Miscellaneous technical information about WANNA SDK.
*/
@interface WsneakersUISDKInfo : NSObject

/**
The WANNASDKCore version.
*/
@property (copy, nonatomic, readonly) NSString* coreSDKVersion;

/**
Is detector feature enabled on device
 */
@property (assign, nonatomic, readonly) BOOL isDetectorEnabled;

/**
Is debug build
 */
@property (assign, nonatomic, readonly) BOOL isDebugBuild;

@end

NS_ASSUME_NONNULL_END
