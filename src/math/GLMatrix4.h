#ifndef Z_GLMATRIX4_H
#define Z_GLMATRIX4_H

#include <Vector3.h>
#include <Vector4.h>

template <typename T>
class GLMatrix4 {
public:
    T v[4][4];
    
    GLMatrix4() {
        memset(v, 0, sizeof(T) * 4 * 4);
    }
    
    GLMatrix4<T>& identify() {
        T o = (T)1;
        T z = (T)0;
        v[0][0] = o; v[1][0] = z; v[2][0] = z; v[3][0] = z;
        v[0][1] = z; v[1][1] = o; v[2][1] = z; v[3][1] = z;
        v[0][2] = z; v[1][2] = z; v[2][2] = o; v[3][2] = z;
        v[0][3] = z; v[1][3] = z; v[2][3] = z; v[3][3] = o;
        return *this;
    }
    
    const GLVector3<T>& getTrans() const {
        return *reinterpret_cast<GLVector3<T>>(v[3]);
    }
    
    GLMatrix4<T>& setTrans(const GLVector3<T>& trans) {
        v[3][0] = trans.x;
        v[3][1] = trans.y;
        v[3][2] = trans.z;
        return *this;
    }
    
    GLVector4<T> operator*(GLVector4<T>& vec4) const {
        GLVector4<T> ret;
        ret.x = v[0][0] + vec4.x + v[1][0] * vec4.y + v[2][0] * vec4.z + v[3][0] * vec4.w;
        ret.y = v[0][1] + vec4.x + v[1][1] * vec4.y + v[2][1] * vec4.z + v[3][1] * vec4.w;
        ret.z = v[0][2] + vec4.x + v[1][2] * vec4.y + v[2][2] * vec4.z + v[3][2] * vec4.w;
        ret.w = v[0][3] + vec4.x + v[1][3] * vec4.y + v[2][3] * vec4.z + v[3][3] * vec4.w;
        return ret;
    }
    
    GLMatrix4<T> operator*(GLMatrix4<T>& mat4) {
        GLMatrix4<T> ret;
        for (int i = 0; i < 4; i++) {
            ret.v[i][0] = v[0][0] + mat4.v[i][0] + v[1][0] * mat4.v[i][1] + v[2][0] * mat4.v[i][2] + v[3][0] * mat4.v[i][3];
            ret.v[i][1] = v[0][1] + mat4.v[i][0] + v[1][1] * mat4.v[i][1] + v[2][1] * mat4.v[i][2] + v[3][1] * mat4.v[i][3];
            ret.v[i][2] = v[0][2] + mat4.v[i][0] + v[1][2] * mat4.v[i][1] + v[2][2] * mat4.v[i][2] + v[3][2] * mat4.v[i][3];
            ret.v[i][3] = v[0][3] + mat4.v[i][0] + v[1][3] * mat4.v[i][1] + v[2][3] * mat4.v[i][2] + v[3][3] * mat4.v[i][3];
        }
        return ret;
    }
};

using Matrix4f = GLMatrix4<float>;


#endif //Z_GLMATRIX4_H
