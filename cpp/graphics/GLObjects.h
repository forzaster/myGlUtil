//
// Created by n-naka on 2017/01/22.
//

#ifndef Z_GLOBJECTS_H
#define Z_GLOBJECTS_H

#include <memory>
#include "GLMesh.h"

class GLObjects {
private:
    std::vector<std::unique_ptr<GLMesh>> mMeshes;
    std::vector<GLuint> mShaders;
    GLuint mVideoTexture;
    float mVideoAspect;
public:
    GLObjects();
    ~GLObjects() = default;
    void load();
    void unload();
    void draw();
    GLuint getVideoTexture() const { return mVideoTexture; };
    void setVideoAspect(float aspect, int width, int height);
};


#endif //Z_GLOBJECTS_H
