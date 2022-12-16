//
// WANNA SDK
// Copyright © 2019 WANNABY Inc. All rights reserved.
//

#import <WsneakersUISDK/WsneakersUISDK.h>
#import <WsneakersUISDK/WsneakersUISDKSession.h>

NS_ASSUME_NONNULL_BEGIN

/**
The video recorder.
*/
@interface WsneakersUISDKSession (RecordingResultVideo)

/**
Starts recording the video of the try-on session.
@param[out] completion a block that receives nil on success or the error object on failure
*/
- (void)startRecordingResultVideoWithCompletion:(void (^)(NSError* _Nullable error))completion;

/**
Starts recording the video of the try-on session.
@param[in] orientation the `UIInterfaceOrientation` constant to specify the video orientation
@param[out] completion a block that receives nil on success or the error object on failure
*/
- (void)startRecordingResultVideoWithOrientation:(UIInterfaceOrientation)orientation
                                      completion:(void (^)(NSError* _Nullable error))completion;

/**
Finishes recording the video of the try-on session.
@param[out] completion a block that receives either the address
where the recording is uploaded or the error object on failure
*/
- (void)stopRecordingResultVideoWithCompletion:(void (^)(
                                                   NSURL* _Nullable videoURL, NSError* _Nullable error))completion;

/*
Overlays the video with the specified image.
@param[in] watermark the image to be used as overlay
*/
- (void)setResultVideoWatermark:(UIImage*)watermark;

@end

NS_ASSUME_NONNULL_END
