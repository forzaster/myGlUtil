#ifndef Z_GLQUATERNION_H
#define Z_GLQUATERNION_H

#include <math.h>
#include "GLVector3.h"

template <typename T>
struct GLQuaternion {
    T x;
    T y;
    T z;
    T w;

public:
    GLQuaternion() : x((T)0), y((T)0), z((T)0), w((T)1) {
    }

    GLQuaternion(T x1, T y1, T z1, T w1) : x(x1), y(y1), z(z1), w(w1) {
    }

    GLQuaternion(const GLQuaternion<T> &v) : x(v.x), y(v.y), z(v.z), w(v.w) {
    }

    GLQuaternion(const GLVector3<T> axis, T theta) {
        float rad2 = (float)theta * M_PI / 180.0f / 2.0f;
        T c = (T)cosf(rad2);
        T s = (T)sinf(rad2);
        x = axis.x * s;
        y = axis.y * s;
        z = axis.z * s;
        w = c;
    }

    GLQuaternion& set(const GLVector3<T> axis, T theta) {
        float rad2 = (float)theta * M_PI / 180.0f / 2.0f;
        T c = (T)cosf(rad2);
        T s = (T)sinf(rad2);
        x = axis.x * s;
        y = axis.y * s;
        z = axis.z * s;
        w = c;
        return *this;
    }

};

using Quaternionf = GLQuaternion<float>;

#endif //Z_GLQUATERNION_H
