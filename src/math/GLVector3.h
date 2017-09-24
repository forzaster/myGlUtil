#ifndef Z_GLVECTOR3_H
#define Z_GLVECTOR3_H

template <typename T>
struct GLVector3 {
public:
    T x;
    T y;
    T z;
    
    GLVector3() : x((T)0), y((T)0), z((T)0) {
    }
    GLVector3(T x1, T y1, T z1, T w1) : x(x1), y(y1), z(z1) {
    }
    GLVector3(const GLVector3 &v) : x(v.x), y(v.y), z(v.z) {
    }
};

using Vector3f = GLVector3<float>;

#endif //Z_GLVECTOR3_H
