#ifndef Z_GLVECTOR4_H
#define Z_GLVECTOR4_H

template <typename T>
struct GLVector4 {
    T x;
    T y;
    T z;
    T w;

public:
    GLVector4() : x((T)0), y((T)0), z((T)0), w((T)1) {
    }
    GLVector4(T x1, T y1, T z1, T w1) : x(x1), y(y1), z(z1), w(w1) {
    }
    GLVector4(const GLVector4 &v) : x(v.x), y(v.y), z(v.z), w(v.w) {
    }
};

using Vector4f = GLVector4<float>;

#endif //Z_GLVECTOR4_H
