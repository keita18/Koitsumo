//! @file 		main.cpp
//! @author 	Keita Tanji
//! @breif		

#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES/gl.h>
#include "glu.h"
#include <math.h>
#include <algorithm>

#include <unistd.h> //sleep用

#include <android/sensor.h>
#include <android_native_app_glue.h>

#include "pch.h"
#include "Engine.h"

#include "Classes/ViewController.h"
#include "Classes/Asset/Asset.h"


/**
 * Initialize an EGL context for the current display.
 */
static int engine_init_display(struct engine* engine) {
    // initialize OpenGL ES and EGL

    LOGI("engine_init_display");


    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;

    /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */
     //有効にするパラメータ
    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_NONE
    };
    
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);

    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria */
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    //nativeActivityへバッファを設定
    ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);
    context = eglCreateContext(display, config, NULL, NULL);

    //EGLレンダリングコンテキストをEGLサーフェイスにアタッチする    
    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOGW("Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    //EGL関連データの保存
    engine->display = display;
    engine->context = context;
    engine->surface = surface;
    engine->width = w;
    engine->height = h;

    //とりあえずここで初期化処理
    Asset::setAssetManager(engine->assetManager);

    //デバッガ接続状態によってはここが二度くるので明示的に初期化
    if(engine->pViewController)
    {
        //旧バージョンからの拡大率
        int wr = w / BASE_SCREEN_WIDTH;
        int hr = h / BASE_SCREEN_HEIGHT;
        Screen::RATIO = std::min(wr, hr);
        Screen::WIDTH = BASE_SCREEN_WIDTH * Screen::RATIO;
        Screen::HEIGHT = BASE_SCREEN_HEIGHT * Screen::RATIO;

        LOGI("SR=%d", Screen::RATIO);

        engine->pViewController->init( Screen::RATIO );
        engine->animating = true;
    }

    //initDraw(engine);

    return 0;
}

/**
 * Just the current frame in the display.
 */
//毎フレームの描画処理
static void engine_draw_frame(struct engine* engine) {
    //LOGI("engine_draw_frame");

    if (engine->display == NULL) {
        // No display.
        return;
    }
    if (engine->pViewController == NULL) return;

    engine->pViewController->drawFrame();

    eglSwapBuffers(engine->display, engine->surface);
}

/**
 * Tear down the EGL context currently associated with the display.
 */
static void engine_term_display(struct engine* engine) {
    if (engine->display != EGL_NO_DISPLAY) {
        eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (engine->context != EGL_NO_CONTEXT) {
            eglDestroyContext(engine->display, engine->context);
        }
        if (engine->surface != EGL_NO_SURFACE) {
            eglDestroySurface(engine->display, engine->surface);
        }
        eglTerminate(engine->display);
    }
    engine->animating = 0;
    engine->display = EGL_NO_DISPLAY;
    engine->context = EGL_NO_CONTEXT;
    engine->surface = EGL_NO_SURFACE;
}

static int32_t onMotionEvnet(struct android_app* app, AInputEvent* event)
{
    struct engine* engine = (struct engine*)app->userData;
    if(engine->pViewController == NULL) return 0;

    // size_t action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK; //emoのやり方
    int32_t action = AMotionEvent_getAction(event);
    // 1点以上押している
    if(action != AKEY_EVENT_ACTION_UP)
    {
        size_t pointCount = AMotionEvent_getPointerCount(event);
        if(pointCount == 1)
        {
            CGPoint pt( AMotionEvent_getX(event, 0), AMotionEvent_getY(event, 0) );
            if(engine->touched == false)
            {
                engine->pViewController->touchesBegan(pt);
                engine->touched = true;
            }
            else 
            {
                engine->pViewController->touchesMoved(pt);                
            }
        }
    }
    // 触ってない
    else
    {
        if(engine->touched == true)
        {
            //@TODO:最後のtouchPoint保持？
            CGPoint pt( AMotionEvent_getX(event, 0), AMotionEvent_getY(event, 0) );
            //CGPoint pt( 0,0 );

            engine->pViewController->touchesEnded(pt);
            engine->touched = false;
        }
    }
}

/**
 * Process the next input event.
 */
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {
    struct engine* engine = (struct engine*)app->userData;
    int type = AInputEvent_getType(event);
    if(type == AINPUT_EVENT_TYPE_MOTION) {
        return onMotionEvnet(app, event);
    }
    //--
    // if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
    //     //アニメーション有効化   
    //     engine->animating = 1;
    //     //タッチ位置を取得
    //     engine->state.x = AMotionEvent_getX(event, 0);
    //     engine->state.y = AMotionEvent_getY(event, 0);
    //     return 1;
    // }
    //return 0;
    //--

    return 0;
}

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
    //LOGI("engine_handle_cmd");

    struct engine* engine = (struct engine*)app->userData;
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            // The system has asked us to save our current state.  Do so.
            engine->app->savedState = malloc(sizeof(struct saved_state));
            *((struct saved_state*)engine->app->savedState) = engine->state;
            engine->app->savedStateSize = sizeof(struct saved_state);
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            if (engine->app->window != NULL) {
                engine_init_display(engine);
                engine_draw_frame(engine);
            }
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
            engine_term_display(engine);
            break;
        case APP_CMD_GAINED_FOCUS:
            // When our app gains focus, we start monitoring the accelerometer.
            if (engine->accelerometerSensor != NULL) {
                ASensorEventQueue_enableSensor(engine->sensorEventQueue,
                        engine->accelerometerSensor);
                // We'd like to get 60 events per second (in us).
                ASensorEventQueue_setEventRate(engine->sensorEventQueue,
                        engine->accelerometerSensor, (1000L/60)*1000);
            }
            break;
        case APP_CMD_LOST_FOCUS:
            // When our app loses focus, we stop monitoring the accelerometer.
            // This is to avoid consuming battery while not being used.
            if (engine->accelerometerSensor != NULL) {
                ASensorEventQueue_disableSensor(engine->sensorEventQueue,
                        engine->accelerometerSensor);
            }
            // Also stop animating.
            engine->animating = 0;
            engine_draw_frame(engine);
            break;
    }
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state) {
    struct engine engine;

    // Make sure glue isn't stripped.
    // glueが削除されないように
    app_dummy();

    LOGI("pin0");
    //デバッガ接続でやるとsleepいれないと動作停止してしまう。このスレッドだけ止まってる感じ。
    sleep(3);

    memset(&engine, 0, sizeof(engine));
    state->userData = &engine;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;
    engine.app = state;

    ViewController viewController(&engine);
    engine.pViewController = &viewController;

    // Prepare to monitor accelerometer
    engine.sensorManager = ASensorManager_getInstance();
    engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
            ASENSOR_TYPE_ACCELEROMETER);
    engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
            state->looper, LOOPER_ID_USER, NULL, NULL);
    // ジャイロスコープのデータ取得準備
    engine.gyroscopeSensor = ASensorManager_getDefaultSensor(
            engine.sensorManager, ASENSOR_TYPE_GYROSCOPE );

    // AssetManagerの取得
    engine.assetManager = state->activity->assetManager;

    if (state->savedState != NULL) {
        // We are starting with a previous saved state; restore from it.
        // 以前の状態に戻す
        engine.state = *(struct saved_state*)state->savedState;
    }

    // loop waiting for stuff to do.

    while (1) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident=ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events,
                (void**)&source)) >= 0) {

            // Process this event.
            if (source != NULL) {
                source->process(state, source);
            }

            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER) {
                if (engine.accelerometerSensor != NULL) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
                            &event, 1) > 0) {
                        // LOGI("accelerometer: x=%f y=%f z=%f",
                        //         event.acceleration.x, event.acceleration.y,
                        //         event.acceleration.z);
                    }
                }
            }

            // Check if we are exiting.
            if (state->destroyRequested != 0) {
                engine_term_display(&engine);
                return;
            }
        }

        // LOGI("pin1");

        if (engine.animating) {
            // Done with events; draw next animation frame.
            engine.state.angle += .01f;
            if (engine.state.angle > 1) {
                engine.state.angle = 0;
            }

            // LOGI("pin2");
            // Drawing is throttled to the screen update rate, so there
            // is no need to do timing here.
            engine_draw_frame(&engine);
        }
    }
}
//END_INCLUDE(all)
