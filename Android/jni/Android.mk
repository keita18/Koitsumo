
LOCAL_PATH := $(call my-dir)

# libpngを利用できるように
# prebuildしたライブラリは直接リンクできない
include $(CLEAR_VARS)
LOCAL_MODULE := libpng15-prebuilt
LOCAL_SRC_FILES := lib/libpng15.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

include $(CLEAR_VARS)
LOCAL_MODULE    := koitsumo
LOCAL_SRC_FILES := main.cpp \
	glu.cpp \
	Classes/Asset/Asset.cpp \
	Classes/Graphics/2D/Sprite.cpp \
	Classes/Routine/MainRoutine.cpp \
	Classes/Routine/Unit.cpp \
	Classes/Routine/Title/TitleUnit.cpp
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv1_CM -lz
LOCAL_STATIC_LIBRARIES := android_native_app_glue
LOCAL_STATIC_LIBRARIES += libpng15-prebuilt
include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
