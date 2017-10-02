//
// Created by n-naka on 2017/01/21.
//

#include "GLMesh.h"

GLMesh::GLMesh(int vertexNum, GLuint buffer, GLuint vba, GLuint program, GLuint texture, Shader shader, Matrix4f* mat)
    : mVertexNum(vertexNum),
      mBuffer(buffer),
      mVBA(vba),
      mProgram(program),
      mTexture(texture),
      mShader(shader) {
    if (mat) {
        mLocalMatrix = *mat;
    }
    mTextureTarget = GL_TEXTURE_2D;
}

GLMesh::~GLMesh() {
}

void GLMesh::updateTexture(GLuint texture, bool externalOes) {
    mTexture = texture;
#ifdef __ANDROID__
    mTextureTarget = externalOes ? GL_TEXTURE_EXTERNAL_OES : GL_TEXTURE_2D;
#else
    mTextureTarget = GL_TEXTURE_2D;
#endif
}

void GLMesh::draw(const Matrix4f& proj) const {
    if (mProgram) {
        glUseProgram(mProgram);
        checkGlError("glUseProgram");
        
        if (mShader == Shader::COLOR_SHADER) {
            static Vector3f axis(0.0f, 1.0f, 0.0f);
            static float theta = 0.0f;
            theta += 1.0f;
            Quaternionf rot(axis, theta);
            Matrix4f mat = mLocalMatrix;
            mat.setRotation(rot);
            mat = proj * mat;
            GLuint id = glGetUniformLocation(mProgram,"mvp");
            glUniformMatrix4fv(id, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(mat.v));
        }

    }

    if (mTexture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(mTextureTarget, mTexture);
    }

    glBindVertexArray(mVBA);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, mVertexNum, 1);

    if (mProgram) {
        glUseProgram(0);
    }
}
