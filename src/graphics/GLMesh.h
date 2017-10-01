//
// Created by n-naka on 2017/01/21.
//

#ifndef Z_GLNODEMESH_H
#define Z_GLNODEMESH_H

#include <vector>
#include "../math/GLMatrix4.h"
#include "Vertex.h"
#include "GLObjectsData.h"

class GLShader;

class GLMesh {
private:
    int mVertexNum;
    GLuint mBuffer;
    GLuint mVBA;
    GLuint mProgram;
    GLuint mTexture;
    GLenum mTextureTarget;
    Shader mShader;
public:
    GLMesh(int vertexNum, GLuint buffer, GLuint vba, GLuint program, GLuint texture, Shader shader);
    virtual ~GLMesh();
    void updateTexture(GLuint texture, bool externalOes);
    void draw(const Matrix4f& proj) const;
    GLuint getBuffer() const { return mBuffer; };
    GLuint getVBA() const { return mVBA; };
};


#endif //Z_GLNODEMESH_H
