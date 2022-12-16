// WANNA SDK
// Copyright © 2021 WANNABY Inc. All rights reserved.

#import <Foundation/Foundation.h>

@class WsneakersUISDKSession;
@class WsneakersUISDKView;

NS_ASSUME_NONNULL_BEGIN

/**
The protocol for an object that handles tips and other info from the session.
*/
@protocol WsneakersUISDKSessionDelegate <NSObject>

/**
Tells you if feet were detected in the frame.

Useful if you want to show the user a tip to point the camera at their feet
so that the sneakers model could be rendered.
@param[in] session current session
@param[out] hasVisibleFeet YES if session detected feet in the frame, otherwise NO
*/
- (void)session:(WsneakersUISDKSession*)session didDetectFeet:(BOOL)hasVisibleFeet;

/**
Informs you that the first frame was processed successfully.

Called only once per session. Use it to start showing the try-on screen.
@param[in] session current session
*/
@optional
- (void)sessionDidProcessFirstFrame:(WsneakersUISDKSession*)session;

/**
 Function to track real scene behavior
 @param[in] sceneReady shows render state
 */
@optional
- (void)session:(WsneakersUISDKSession*)session didLoadScene:(BOOL)sceneReady;

@end

NS_ASSUME_NONNULL_END
