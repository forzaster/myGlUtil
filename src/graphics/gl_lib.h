//
// Created by n-naka on 2016/12/31.
//

#ifndef _GL_LIB_H
#define _GL_LIB_H

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#define GLESv3

#ifdef TARGET_OS_IPHONE

#ifdef GLESv3
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#else
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#endif

#else

#ifdef GLESv3
#include <GLES3/gl3.h>
#else
#include <GLES2/gl2.h>
#endif

#include <GLES2/gl2ext.h>

#endif

#include "../Log.h"

static __inline void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static __inline void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

#endif //_GL_LIB_H
