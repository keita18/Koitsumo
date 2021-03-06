#pragma once

#include <cstddef>
#include <cassert>

#include <android/log.h>

#include <math.h>

#include "Classes/Graphics/GRDefinition.h"
#include "Classes/Math/Vector2.h"

#define TAG "Koitsumo"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Koitsumo", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Koitsumo", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "Koitsumo", __VA_ARGS__))

#define SAFE_DELETE(p) { if(p!=NULL) { delete p; p = NULL; } }
#define SAFE_DELETE_ARRAY( x ) { delete[] x; x = 0; }
