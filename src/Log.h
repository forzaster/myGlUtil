//
// Created by n-naka on 2016/12/30.
//

#ifndef _LOG_H
#define _LOG_H

#ifdef __ANDROID__
#include <android/log.h>

#define  LOG_TAG    "GLES"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#else defined(IOS)

#define  LOGI(...)
#define  LOGE(...)

#else

#define  LOGI(...)
#define  LOGE(...)

#endif

#endif //_LOG_H
