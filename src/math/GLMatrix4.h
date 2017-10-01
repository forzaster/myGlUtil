#ifndef Z_GLMATRIX4_H
#define Z_GLMATRIX4_H

#include "Log.h"
#include "GLVector3.h"
#include "GLVector4.h"
#include "GLQuaternion.h"

template <typename T>
struct GLMatrix4 {
public:
    T v[4][4];
    
    GLMatrix4() {
        identify();
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
    
    GLMatrix4<T>& setRotation(const GLQuaternion<T> q) {
        T qx2 = q.x * q.x;
        T qy2 = q.y * q.y;
        T qz2 = q.z * q.z;
        T qw2 = q.w * q.w;
        T qxy = q.x * q.y;
        T qxz = q.x * q.z;
        T qxw = q.x * q.w;
        T qyz = q.y * q.z;
        T qyw = q.y * q.w;
        T qzw = q.z * q.w;
        v[0][0] = qx2 + qy2 - qz2 - qw2;
        v[1][0] = ((T)2.0f) * (qyz - qxw);
        v[2][0] = ((T)2.0f) * (qyw - qxz);
        v[0][1] = ((T)2.0f) * (qyz + qxw);
        v[1][1] = qx2 - qy2 + qz2 - qw2;
        v[2][1] = ((T)2.0f) * (qzw - qxy);
        v[0][2] = ((T)2.0f) * (qyw - qxz);
        v[1][2] = ((T)2.0f) * (qzw + qxy);
        v[2][2] = qx2 - qy2 - qz2 + qw2;
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
    
    GLMatrix4<T> operator*(const GLMatrix4<T>& mat4) const {
        GLMatrix4<T> ret;
        for (int i = 0; i < 4; i++) {
            ret.v[i][0] = v[0][0] * mat4.v[i][0] + v[1][0] * mat4.v[i][1] + v[2][0] * mat4.v[i][2] + v[3][0] * mat4.v[i][3];
            ret.v[i][1] = v[0][1] * mat4.v[i][0] + v[1][1] * mat4.v[i][1] + v[2][1] * mat4.v[i][2] + v[3][1] * mat4.v[i][3];
            ret.v[i][2] = v[0][2] * mat4.v[i][0] + v[1][2] * mat4.v[i][1] + v[2][2] * mat4.v[i][2] + v[3][2] * mat4.v[i][3];
            ret.v[i][3] = v[0][3] * mat4.v[i][0] + v[1][3] * mat4.v[i][1] + v[2][3] * mat4.v[i][2] + v[3][3] * mat4.v[i][3];
        }
        return ret;
    }
    
    GLMatrix4<T>& operator*= (GLMatrix4<T>& mat4) {
        GLMatrix4<T> ret;
        for (int i = 0; i < 4; i++) {
            ret.v[i][0] = v[0][0] * mat4.v[i][0] + v[1][0] * mat4.v[i][1] + v[2][0] * mat4.v[i][2] + v[3][0] * mat4.v[i][3];
            ret.v[i][1] = v[0][1] * mat4.v[i][0] + v[1][1] * mat4.v[i][1] + v[2][1] * mat4.v[i][2] + v[3][1] * mat4.v[i][3];
            ret.v[i][2] = v[0][2] * mat4.v[i][0] + v[1][2] * mat4.v[i][1] + v[2][2] * mat4.v[i][2] + v[3][2] * mat4.v[i][3];
            ret.v[i][3] = v[0][3] * mat4.v[i][0] + v[1][3] * mat4.v[i][1] + v[2][3] * mat4.v[i][2] + v[3][3] * mat4.v[i][3];
        }
        *this = ret;
        return *this;
    }

    GLMatrix4<T>& perspective(T left, T top, T right, T bottom, T near, T far) {
        identify();
        v[0][0] = (T)2.0f * near / (right - left);
        v[2][0] = (right + left) / (right - left);
        v[1][1] = (T)2.0f * near / (top - bottom);
        v[2][1] = (top + bottom) / (top - bottom);
        v[2][2] = -(far + near) / (far - near);
        v[3][2] = - (T)2.0f * far * near / (far - near);
        v[2][3] = -(T)1.0f;
        v[3][3] = (T)0.0f;
        return *this;
    }
    
    void dump() const {
        LOGI("%f %f %f %f¥n", v[0][0], v[1][0], v[2][0], v[3][0]);
        LOGI("%f %f %f %f¥n", v[0][1], v[1][1], v[2][1], v[3][1]);
        LOGI("%f %f %f %f¥n", v[0][2], v[1][2], v[2][2], v[3][2]);
        LOGI("%f %f %f %f¥n", v[0][3], v[1][3], v[2][3], v[3][3]);
    }
};

using Matrix4f = GLMatrix4<float>;


#endif //Z_GLMATRIX4_H
