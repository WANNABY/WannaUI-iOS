//
// WANNA SDK
// Copyright © 2021 WANNABY Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WsneakersUISDKViewerNode : NSObject

@property (nonatomic, strong) NSString* name;
@property (nonatomic, strong) NSString* identifier;

- (id)initWithName:(NSString*)name identifier:(NSString*)identifier;

@end

NS_ASSUME_NONNULL_END
