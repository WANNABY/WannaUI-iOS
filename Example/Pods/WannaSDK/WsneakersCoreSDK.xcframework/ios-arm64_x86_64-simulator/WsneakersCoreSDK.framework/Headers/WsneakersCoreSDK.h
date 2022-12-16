//
// WANNA SDK
// Copyright © 2018 WANNABY Inc. All rights reserved.
//

#ifndef SDKS_WSNEAKERS_CORE_CORE_WSNEAKERSCORESDK_H_
#define SDKS_WSNEAKERS_CORE_CORE_WSNEAKERSCORESDK_H_

#if defined(__cplusplus)
#define WSNEAKERSCORESDK_EXTERN extern "C"
#else
#define WSNEAKERSCORESDK_EXTERN extern
#endif

#include <stdbool.h>
#include <stdlib.h>

typedef enum {
    WSNEAKERSCORESDK_RESULT_SUCCESS = 0,
    WSNEAKERSCORESDK_RESULT_FAILURE = 1,
    WSNEAKERSCORESDK_RESULT_NO_RENDER_MODEL = 2,
    WSNEAKERSCORESDK_RESULT_FRAME_SKIPPED = 3,
    WSNEAKERSCORESDK_RESULT_PENDING = 4,
    WSNEAKERSCORESDK_RESULT_CANCEL = 5,
    WSNEAKERSCORESDK_RESULT_ERROR_INTERNAL = 6,
    WSNEAKERSCORESDK_RESULT_ACCESS_DENIED = 7,
    WSNEAKERSCORESDK_RESULT_ERROR_NETWORK = 8,
    WSNEAKERSCORESDK_RESULT_ERROR_NETWORK_CONNECTION = 9,
    WSNEAKERSCORESDK_RESULT_ERROR_NETWORK_TIMEOUT = 10,
    WSNEAKERSCORESDK_RESULT_ERROR_SERVER = 11,
    WSNEAKERSCORESDK_RESULT_ERROR_PROTOCOL = 12,
    WSNEAKERSCORESDK_RESULT_ERROR_UNSUPPORTED_VERSION = 13,
    WSNEAKERSCORESDK_RESULT_ERROR_BAD_CALL = 14,
    WSNEAKERSCORESDK_RESULT_ERROR_INV_CACHE = 15,
    WSNEAKERSCORESDK_RESULT_ERROR_UNSUPPORTED_DEVICE = 16,
    WSNEAKERSCORESDK_RESULT_ERROR_BAD_LICENSE = 17,
    WSNEAKERSCORESDK_RESULT_ERROR_LICENSE_EXPIRED = 18,
    WSNEAKERSCORESDK_RESULT_ERROR_NO_COMPLETION_CALLBACK = 19,
    WSNEAKERSCORESDK_RESULT_ERROR_BAD_DATA_PACK = 20,
    WSNEAKERSCORESDK_RESULT_ERROR_DEPRECATED = 21
} WSNEAKERSCORESDK_RESULT;

typedef enum {
    WSNEAKERSCORESDK_FRAME_FORMAT_RAWBGRA32 = 0,
    WSNEAKERSCORESDK_FRAME_FORMAT_RAWABGR32,
    WSNEAKERSCORESDK_FRAME_FORMAT_IOS_SAMPLEBUFFER,
    WSNEAKERSCORESDK_FRAME_FORMAT_IOS_TEXTURE,
    WSNEAKERSCORESDK_FRAME_FORMAT_ANDROID_TEXTURE,
    WSNEAKERSCORESDK_FRAME_FORMAT_ANDROID_TEXTURE_EXTERNAL_OES
} WSNEAKERSCORESDK_FRAME_FORMAT;

struct WsneakersCoreSDKCameraIntrinsics {
    float fx;
    float fy;
    float x0;
    float y0;
};

struct WsneakersCoreSDKFrameInfo {
    void* data_pointer;
    WSNEAKERSCORESDK_FRAME_FORMAT frame_format;
    int width;
    int height;
    int bytes_per_row;
    void* transform_matrix;
    void* user_data;

    void* captureDevice;
    struct WsneakersCoreSDKCameraIntrinsics camera_intrinsics;

    // <bookmark>
    // This field is reserved for internal use only. Values other than zero may
    // result in undefined behavior. In the future, the field can be purged from the public API
    // altogether without any notice. The underlaying type and the size of the structure is
    // also subject to change.
    // </bookmark>
    unsigned reserved;
};

// fast performing iOS specific API
struct WsneakersCoreSDKProcessingInfo {
    bool has_visible_feet;
    bool rendering_occurred;
    bool scene_ready;
    bool pipeline_ready;
    unsigned short camera_focus_x;
    unsigned short camera_focus_y;
};

typedef void (*WsneakersCoreSDKFrameCompletionFunction)(struct WsneakersCoreSDKFrameInfo frame_info,
    WSNEAKERSCORESDK_RESULT result, struct WsneakersCoreSDKProcessingInfo processingInfo, void* user_data);

typedef void (*WsneakersCoreSDKFrameReleaseDataFunction)(struct WsneakersCoreSDKFrameInfo frame_info, void* user_data);

typedef enum {
    WSNEAKERSCORESDK_PROGRESS_CANCEL = 0,
    WSNEAKERSCORESDK_PROGRESS_CONTINUE,
} WSNEAKERSCORESDK_PROGRESS;

typedef WSNEAKERSCORESDK_PROGRESS (*WsneakersCoreSDKProgressFunction)(float progress, void* user_data);

typedef enum {
    WSNEAKERSCORESDK_LOG_EVENT_TYPE_INFO = 0,
    WSNEAKERSCORESDK_LOG_EVENT_TYPE_WARNING,
    WSNEAKERSCORESDK_LOG_EVENT_TYPE_ERROR,
    WSNEAKERSCORESDK_LOG_EVENT_TYPE_DUMP,
} WSNEAKERSCORESDK_LOG_EVENT_TYPE;

struct WsneakersCoreSDKLogEventParamsEntry {
    const char* key;
    const char* value;
};

struct WsneakersCoreSDKLogEventParams {
    struct WsneakersCoreSDKLogEventParamsEntry* entries;
    size_t entry_count;
};

typedef void (*WsneakersCoreSDKLogEventFunction)(
    int log_level, const char* event_name, struct WsneakersCoreSDKLogEventParams params, void* user_data);

typedef void (*WsneakersCoreSDKLogEventUserDataReleaseFunc)(void*);

typedef void* WsneakersCoreSDKSessionRef;

typedef enum {
    WSNEAKERSCORESDK_RENDER_OBJECT_TYPE_SNEAKERS,
    WSNEAKERSCORESDK_RENDER_OBJECT_TYPE_WATCH,
    WSNEAKERSCORESDK_RENDER_OBJECT_TYPE_BAG,
} WSNEAKERSCORESDK_RENDER_OBJECT_TYPE;

//! Get datapack version
WSNEAKERSCORESDK_EXTERN const char* WsneakersCoreSDKGetDataPackVersion(
    WSNEAKERSCORESDK_RENDER_OBJECT_TYPE session_type);

typedef struct {
    bool isDetectorEnabled;
    bool isDebugBuild;
} WsneakersCoreSDKSessionConfiguration;

//! Get session configuration — internal use only
WSNEAKERSCORESDK_EXTERN const WsneakersCoreSDKSessionConfiguration __attribute__((visibility("default")))
WsneakersCoreSDKSessionGetConfiguration(void);

//! Creates session
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSessionCreateWithType(
    WsneakersCoreSDKSessionRef* session, WSNEAKERSCORESDK_RENDER_OBJECT_TYPE session_type, bool watermark);

struct WsneakersCoreSDKDataPackEntry {
    const char* key;
    const char* path;
};

struct WsneakersCoreSDKDataPack {
    struct WsneakersCoreSDKDataPackEntry* entries;
    size_t entry_count;
};

//! Set data pack for session
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSessionSetDataPack(
    WsneakersCoreSDKSessionRef session, struct WsneakersCoreSDKDataPack datapack);

//! Creates session
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSessionCreate(const char* client_config,
    WsneakersCoreSDKSessionRef* session, WsneakersCoreSDKProgressFunction callback, void* user_data);

//! Creates watch session
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKWatchSessionCreate(const char* client_config,
    WsneakersCoreSDKSessionRef* session, WsneakersCoreSDKProgressFunction callback, void* user_data);

//! Destroys session
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSessionDestroy(WsneakersCoreSDKSessionRef session);

//! Sets frame completion callback
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSessionSetFrameCompletion(
    WsneakersCoreSDKSessionRef session, WsneakersCoreSDKFrameCompletionFunction function, void* user_data);

//! Sets frame data release callback
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSessionSetFrameReleaseData(
    WsneakersCoreSDKSessionRef session, WsneakersCoreSDKFrameReleaseDataFunction function, void* user_data);

//! Sets errors callback
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSessionSetLogEventCallback(
    WsneakersCoreSDKLogEventFunction function, void* user_data,
    WsneakersCoreSDKLogEventUserDataReleaseFunc release_data);

//! Pushes next frame to handling
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSessionPushFrame(
    WsneakersCoreSDKSessionRef session, struct WsneakersCoreSDKFrameInfo frame_info);

typedef void* WsneakersCoreSDKSceneControllerRef;

//! Returns scene controller
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSessionGetSceneController(
    WsneakersCoreSDKSessionRef session, WsneakersCoreSDKSceneControllerRef* scene_controller);

//! Creates 3d viewer session
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSessionViewerCreate(const char* client_config,
    WsneakersCoreSDKSessionRef* session, WsneakersCoreSDKProgressFunction callback, void* user_data);

//! Sets vieweport size
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSessionViewerSetViewport(
    WsneakersCoreSDKSessionRef session, unsigned int height, unsigned int width);

typedef struct {
    float yaw;
    float pitch;
} WsneakersCoreSDKRotation;

//! Rotates 3d model
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneRotateTarget(
    WsneakersCoreSDKSceneControllerRef scene_controller, WsneakersCoreSDKRotation rotation);

//! Scales 3d model
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneSetScale(
    WsneakersCoreSDKSceneControllerRef scene_controller, float scale);

typedef struct {
    WsneakersCoreSDKRotation rotation;
    float scale;
} WsneakersCoreSDKCameraPosition;

//! Get camera position
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneGetCameraPosition(
    WsneakersCoreSDKSceneControllerRef scene_controller, WsneakersCoreSDKCameraPosition* position);

//! Set camera position
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneSetCameraPosition(
    WsneakersCoreSDKSceneControllerRef scene_controller, const WsneakersCoreSDKCameraPosition* position);

typedef struct {
    float x;
    float y;
    float z;
} WsneakersCoreSDKPoint;

//! Get camera POI
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneGetCameraPOI(
    WsneakersCoreSDKSceneControllerRef scene_controller, WsneakersCoreSDKPoint* poi);

//! Set camera POI
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneSetCameraPOI(
    WsneakersCoreSDKSceneControllerRef scene_controller, const WsneakersCoreSDKPoint* poi);

typedef void (*WsneakersCoreSDKSceneOnCameraChangeCallback)(
    const WsneakersCoreSDKCameraPosition* position, const WsneakersCoreSDKPoint* poi, void* user_data);

//! Subscribe on camera position and POI updates
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneSetOnCameraChangeCallback(
    WsneakersCoreSDKSceneControllerRef scene_controller, WsneakersCoreSDKSceneOnCameraChangeCallback callback,
    void* user_data);

typedef unsigned int WsneakersCoreSDKObjectIndex;

static const WsneakersCoreSDKObjectIndex kWsneakersCoreSDKLeftSneakerObject = 0;
static const WsneakersCoreSDKObjectIndex kWsneakersCoreSDKRightSneakerObject = 1;

typedef struct {
    WsneakersCoreSDKCameraPosition position;
    WsneakersCoreSDKPoint poi;
} WsneakersCoreSDKCameraConfiguration;

typedef struct {
    float object_length;
    float min_scale;
    float max_scale;
    WsneakersCoreSDKCameraConfiguration dimensions_view_camera;
    WsneakersCoreSDKCameraConfiguration fallback_camera;
} WsneakersCoreSDKSceneObjectConfiguration;

//! Get object configuration
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneGetObjectConfiguration(
    WsneakersCoreSDKSceneControllerRef scene_controller, WsneakersCoreSDKObjectIndex index,
    WsneakersCoreSDKSceneObjectConfiguration* configuration);

//! Set object configuration
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneSetObjectConfiguration(
    WsneakersCoreSDKSceneControllerRef scene_controller, WsneakersCoreSDKObjectIndex index,
    const WsneakersCoreSDKSceneObjectConfiguration* configuration);

//! Select a specific object
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKScenePresentObject(
    WsneakersCoreSDKSceneControllerRef scene_controller, WsneakersCoreSDKObjectIndex index);

typedef struct {
    WsneakersCoreSDKPoint min;
    WsneakersCoreSDKPoint max;
} WsneakersCoreSDKBoundingBox;

//! Get object bounding box
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneGetObjectBoundingBox(
    WsneakersCoreSDKSceneControllerRef scene_controller, WsneakersCoreSDKObjectIndex index,
    WsneakersCoreSDKBoundingBox* bounding_box);

typedef struct WsneakersCoreSDKSceneNode WsneakersCoreSDKSceneNode;

typedef struct {
    size_t size;
    WsneakersCoreSDKSceneNode* nodes;
} WsneakersCoreSDKSceneNodeCollection;

typedef void* WsneakersCoreSDKSceneNodeRef;

typedef enum {
    WSNEAKERSCORESDK_SCENE_NODE_TYPE_UNKNOWN = 0,

    WSNEAKERSCORESDK_SCENE_NODE_TYPE_MAIN = 1,
    WSNEAKERSCORESDK_SCENE_NODE_TYPE_PLANE_AO = 2,
    WSNEAKERSCORESDK_SCENE_NODE_TYPE_STRAP_LONG = 3,
    WSNEAKERSCORESDK_SCENE_NODE_TYPE_PLANE_AO_STRAP = 4,
    WSNEAKERSCORESDK_SCENE_NODE_TYPE_DIMENSION_CM = 5,
    WSNEAKERSCORESDK_SCENE_NODE_TYPE_DIMENSION_INCH = 6,

    WSNEAKERSCORESDK_SCENE_NODE_TYPE_CAMERA = (1 << 8),
} WSNEAKERSCORESDK_SCENE_NODE_TYPE;

struct WsneakersCoreSDKSceneNode {
    unsigned int idx;
    char* name;
    WSNEAKERSCORESDK_SCENE_NODE_TYPE type;
    WsneakersCoreSDKBoundingBox bounding_box;
    WsneakersCoreSDKSceneNodeRef ref;
    WsneakersCoreSDKSceneNodeCollection children;
};

//! Get object nodes
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneGetObjectNodes(
    WsneakersCoreSDKSceneControllerRef scene_controller, WsneakersCoreSDKObjectIndex index,
    WsneakersCoreSDKSceneNodeCollection* nodes);

//! Show/hide object node
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneSetObjectNodeVisible(
    WsneakersCoreSDKSceneControllerRef scene_controller, WsneakersCoreSDKObjectIndex index,
    WsneakersCoreSDKSceneNodeRef node, bool visible, bool with_descendants);

//! Set object node as  camera
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneSetCameraFromObjectNode(
    WsneakersCoreSDKSceneControllerRef scene_controller, WsneakersCoreSDKObjectIndex index,
    WsneakersCoreSDKSceneNodeRef node);

typedef void* WsneakersCoreSDKAnimation;

//! Applies animation
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKAnimationApply(
    WsneakersCoreSDKAnimation animation, float time);

//! Destroys animation
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKAnimationDestroy(WsneakersCoreSDKAnimation animation);

//! Creates linear fade out animation for node
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneCreateLinearFadeOutAnimation(
    WsneakersCoreSDKSceneControllerRef scene_controller, WsneakersCoreSDKObjectIndex index,
    WsneakersCoreSDKSceneNodeRef node, WsneakersCoreSDKAnimation* animation);

typedef struct {
    WsneakersCoreSDKCameraPosition* control_points;
    size_t size;
} WsneakersCoreSDKCameraMoveBezierCurveControlPoints;

typedef WsneakersCoreSDKCameraMoveBezierCurveControlPoints (*WsneakersCoreSDKMakeBezierCurveControlPointsFunction)(
    const WsneakersCoreSDKCameraPosition* start_point, const WsneakersCoreSDKCameraPosition* end_point,
    void* user_data);

//! Creates an animation of moving the camera from its current position to the given camera node along a Bezier curve.
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneCreateBezierCurveCameraMoveToNodeAnimation(
    WsneakersCoreSDKSceneControllerRef scene_controller, WsneakersCoreSDKObjectIndex index,
    WsneakersCoreSDKSceneNodeRef dst_node, WsneakersCoreSDKMakeBezierCurveControlPointsFunction make_control_points,
    void* user_data, WsneakersCoreSDKAnimation* animation);

//! Creates an animation of moving the camera from its current position to the given point along a Bezier curve.
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSceneCreateBezierCurveCameraMoveToPointAnimation(
    WsneakersCoreSDKSceneControllerRef scene_controller, WsneakersCoreSDKObjectIndex index,
    const WsneakersCoreSDKCameraPosition* dst_pos, const WsneakersCoreSDKPoint* dst_poi,
    WsneakersCoreSDKMakeBezierCurveControlPointsFunction make_control_points, void* user_data,
    WsneakersCoreSDKAnimation* animation);

typedef void* WsneakersCoreSDKLibraryRef;

//! Returns library
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSessionGetLibrary(
    WsneakersCoreSDKSessionRef session, WsneakersCoreSDKLibraryRef* library);

typedef enum {
    WSNEAKERSCORESDK_BEZIER_CURVE_MAKER_CUBIC_DEFAULT = 0,
} WSNEAKERSCORESDK_BEZIER_CURVE_MAKER;

//! Returns Bezier curve control points maker
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKLibraryBezierCurveControlPointsMaker(
    WsneakersCoreSDKLibraryRef library, WSNEAKERSCORESDK_BEZIER_CURVE_MAKER maker,
    WsneakersCoreSDKMakeBezierCurveControlPointsFunction* func, void** user_data);

typedef void* WsneakersCoreSDKRenderModelRef;

//! Creates empty render model
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKRenderModelCreateEmpty(
    WsneakersCoreSDKRenderModelRef* render_model);

//! Creates render model using content of description file *.pbascii
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKRenderModelCreateWithContentOfFile(
    const char* path, WsneakersCoreSDKRenderModelRef* render_model);

typedef void* WsneakersCoreSDKRenderModelStorageRef;

//! Creates render model previously saved in storage, NULL if some part was not persisted in cache
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKRenderModelCachedCreate(
    WsneakersCoreSDKRenderModelStorageRef storage, const char* render_model_id,
    WsneakersCoreSDKRenderModelRef* render_model);

//! Creates storage with remote render models
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKRenderModelStorageCreate(
    const char* client_config, size_t cache_size, WsneakersCoreSDKRenderModelStorageRef* storage);

typedef void (*WsneakersCoreSDKStorageUpdateCallback)(
    WsneakersCoreSDKRenderModelRef render_model, const char* render_model_id, void* user_data);

//! Subscribe on updates from storage
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKRenderModelStorageSetCallback(
    WsneakersCoreSDKRenderModelStorageRef storage, WsneakersCoreSDKStorageUpdateCallback callback, void* user_data);

//! Destroys storage
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKRenderModelStorageDestroy(
    WsneakersCoreSDKRenderModelStorageRef storage);

//! Clears cache
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKRenderModelStorageClearCache(
    WsneakersCoreSDKRenderModelStorageRef storage);

//! Create render model using remote storage
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKRenderModelCreate(
    WsneakersCoreSDKRenderModelStorageRef storage, const char* render_model_id,
    WsneakersCoreSDKRenderModelRef* render_model, WsneakersCoreSDKProgressFunction callback, void* user_data);

//! Create render model with url using remote storage
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKRenderModelCreateWithURL(
    WsneakersCoreSDKRenderModelStorageRef storage, const char* url, WsneakersCoreSDKRenderModelRef* render_model,
    WsneakersCoreSDKProgressFunction callback, void* user_data);

//! Loads render model to storage
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKRenderModelPreload(
    WsneakersCoreSDKRenderModelStorageRef storage, const char* render_model_id,
    WsneakersCoreSDKProgressFunction callback, void* user_data);

//! Load  render model from given path with files from datapack
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSessionSetRenderModelWithDataPack(
    WsneakersCoreSDKSessionRef session, const char* model_id, const char* render_model_path,
    struct WsneakersCoreSDKDataPack datapack);

struct WsneakersCoreSDKRenderModelInfo {
    char* render_model_id;
    char* render_model_type;
    size_t created_at;
    size_t updated_at;
    void* user_data;
};

struct WsneakersCoreSDKRenderModelCollection {
    size_t size;
    struct WsneakersCoreSDKRenderModelInfo* models;
};

//! Creates collection with available render models
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKRenderModelCollectionCreate(
    WsneakersCoreSDKRenderModelStorageRef storage, struct WsneakersCoreSDKRenderModelCollection* collection);

//! Destroys collection
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKRenderModelCollectionDestroy(
    struct WsneakersCoreSDKRenderModelCollection collection);

//! Destroys render model
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKRenderModelDestroy(
    WsneakersCoreSDKRenderModelRef render_model);

//! Sets render model to session
//! For 3D viewer this must be called after viewport size set
//! (e.g., by invoke of WsneakersCoreSDKSessionViewerSetViewport or WsneakersCoreSDKSessionPushFrame)
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKSessionSetRenderModel(
    WsneakersCoreSDKSessionRef session, WsneakersCoreSDKRenderModelRef render_model);

//! Internal service api, don't use it
WSNEAKERSCORESDK_EXTERN WSNEAKERSCORESDK_RESULT WsneakersCoreSDKServiceApi(void** api);

//! Returns SDK version
WSNEAKERSCORESDK_EXTERN const char* WsneakersCoreSDKGetVersion(void);

#endif  // SDKS_WSNEAKERS_CORE_CORE_WSNEAKERSCORESDK_H_
