#ifndef Z_GLQUATERNION_H
#define Z_GLQUATERNION_H

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
    GLQuaternion(const GLQuaternion &v) : x(v.x), y(v.y), z(v.z), w(v.w) {
    }
};

using Quaternionf = GLQuaternion<float>;

#endif //Z_GLQUATERNION_H
