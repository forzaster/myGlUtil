//
// Created by n-naka on 2017/01/22.
//

#ifndef Z_GLOBJECTS_H
#define Z_GLOBJECTS_H

#include <memory>
#include "../math/GLQuaternion.h"
#include "../math/GLMatrix4.h"
#include "GLMesh.h"
#include "GLShader.h"

class GLObjects {
private:
    std::vector<std::unique_ptr<GLMesh>> mMeshes;
    std::vector<std::unique_ptr<GLShader>> mShaders;
    GLuint mVideoTexture;
    GLuint mTexture;
    float mVideoAspect;
    Vector3f mCameraPos;
    Quaternionf mCameraQuat;
    Matrix4f mProjection;
    
public:
    GLObjects();
    ~GLObjects() = default;
    void load();
    void unload();
    void draw();
    GLuint getVideoTexture() const { return mVideoTexture; };
    void setVideoAspect(float videoAspect, float surfaceAspect);
    void setPerspective(float aspect, float fovY, float zNear, float zFar);
    void setImage(int width, int height, int bytesPerPixel, const uint8_t* data);
};


#endif //Z_GLOBJECTS_H
