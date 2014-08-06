//! @file         Engine.h
//! @author     Keita Tanji
//! @breif        
#pragma once

#include <jni.h>
#include <errno.h>

#include <android/sensor.h>
#include <android_native_app_glue.h>
#include <android/asset_manager.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

class ViewController;

/**
 * Our saved state data.
 */
struct saved_state {
    float angle;
    int32_t x;
    int32_t y;
};

/**
 * Shared state for our app.
 */
struct engine {
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    const ASensor* gyroscopeSensor;
    ASensorEventQueue* sensorEventQueue;

    int animating;

    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;

    int32_t width;
    int32_t height;

    struct saved_state state;

    AAssetManager* assetManager;
    ViewController* pViewController;
};
