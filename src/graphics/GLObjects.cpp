//
// Created by n-naka on 2017/01/22.
//

#include <string>
#include <functional>
#include <math.h>
#include "../Log.h"
#include "../math/GLMatrix4.h"

#include "Vertex.h"
#include "GLObjects.h"
#include "GLObjectsData.h"

#include "GLShader.h"
#include "SpriteShader.h"
#include "ColorShader.h"
#include "TextureShader.h"
#include "SobelShader.h"
#include "VideoTextureShader.h"

using GEN_VIDEO_TEX_FUNC = GLuint (*)(void);

static GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = new char[infoLen];
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                         shaderType, buf);
                    delete[] buf;
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

static GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = new char[bufLength];
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    delete[] buf;
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

static void createVBA(GLuint *buffer, GLuint* vba, const Vertex *vertex, int size) {
    glGenBuffers(1, buffer);
    glBindBuffer(GL_ARRAY_BUFFER, *buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * size, vertex, GL_STATIC_DRAW);

    glGenVertexArrays(1, vba);
    glBindVertexArray(*vba);

    glBindBuffer(GL_ARRAY_BUFFER, *vba);
    glVertexAttribPointer(POS_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, pos));
    glVertexAttribPointer(COLOR_ATTRIB, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, rgba));
    glVertexAttribPointer(UV_ATTRIB, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(POS_ATTRIB);
    glEnableVertexAttribArray(COLOR_ATTRIB);
    glEnableVertexAttribArray(UV_ATTRIB);
    
    glBindVertexArray(0);
}

static void deleteVBA(GLuint buffer, GLuint vba) {
    if (vba) {
        glDeleteVertexArrays(1, &vba);
    }
    if (buffer) {
        glDeleteBuffers(1, &buffer);
    }
}

static GLuint genNormalTexture() {
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    return texture;
}

#ifdef __ANDROID__
static std::function<GLuint(void)> sGenVideoTexFunc = []() -> GLuint {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, texture);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    return texture;
};
#else
static std::function<GLuint(void)> sGenVideoTexFunc = nullptr;
#endif

GLObjects::GLObjects() :
mVideoTexture(0),
mTexture(0) {
}

void GLObjects::load() {
    mShaders.push_back(std::unique_ptr<GLShader>(new SpriteShader(createProgram(SpriteShader::vs().c_str(), SpriteShader::fs().c_str()), Shader::SPRITE_SHADER)));
    mShaders.push_back(std::unique_ptr<GLShader>(new ColorShader(createProgram(ColorShader::vs().c_str(), ColorShader::fs().c_str()), Shader::COLOR_SHADER)));
    mShaders.push_back(std::unique_ptr<GLShader>(new TextureShader(createProgram(TextureShader::vs().c_str(), TextureShader::fs().c_str()), Shader::TEXTURE_SHADER)));
    mShaders.push_back(std::unique_ptr<GLShader>(new SobelShader(createProgram(SobelShader::vs().c_str(), SobelShader::fs().c_str()), Shader::SOBEL_SHADER)));
#ifdef __ANDROID__
    mShaders.push_back(std::unique_ptr<GLShader>(new VideoTextureShader(createProgram(VideoTextureShader::vs().c_str(), VideoTextureShader::fs().c_str()), Shader::VIDEO_TEXTURE_SHADER)));
#endif
    
    if (sGenVideoTexFunc) {
        mVideoTexture = sGenVideoTexFunc();
    }
    
    mTexture = genNormalTexture();
    
    int meshNum = sizeof(sMeshes) / sizeof(Mesh);
    for (int i = 0; i < meshNum; i++) {
        GLuint buffer, vba;
        int size = sMeshes[i].vertexSize;
        GLShader* shader = mShaders.at(static_cast<int>(sMeshes[i].shader)).get();
        createVBA(&buffer, &vba, sMeshes[i].vertex, size);
        Matrix4f mat;
        mat.identify().setTrans(sMeshes[i].posInWorld);
        mMeshes.push_back(std::unique_ptr<GLMesh>(new GLMesh{size, buffer, vba, 0, shader, &mat}));
#ifdef __ANDROID__
        if (sMeshes[i].shader == Shader::VIDEO_TEXTURE_SHADER) {
            mMeshes.at(mMeshes.size()-1)->updateTexture(mVideoTexture, true);
        }
#endif
        if (sMeshes[i].shader == Shader::TEXTURE_SHADER) {
            mMeshes.at(mMeshes.size()-1)->updateTexture(mTexture, false);
        }
    }
}

void GLObjects::unload() {
    for (auto it = mShaders.begin(); it != mShaders.end(); ++it) {
        (*it)->unload();
    }
    mShaders.clear();

    for (auto it = mMeshes.begin(); it != mMeshes.end(); ++it) {
        deleteVBA((*it)->getBuffer(), (*it)->getVBA());
    }
    mMeshes.clear();

    if (mVideoTexture) {
        glDeleteTextures(1, &mVideoTexture);
        mVideoTexture = 0;
    }
    
    if (mTexture) {
        glDeleteTextures(1, &mTexture);
        mTexture = 0;
    }
}

void GLObjects::draw() {
    for (auto it = mMeshes.begin(); it != mMeshes.end(); ++it) {
        (*it)->draw(mProjection);
    }
}

void GLObjects::setVideoAspect(float videoAspect, float surfaceAspect) {
    mVideoAspect = videoAspect;
    if (surfaceAspect < mVideoAspect) {
        float y = (1.0f / mVideoAspect) / (1.0f / surfaceAspect);
        sVertex1[0].pos[1] = -y;
        sVertex1[1].pos[1] = -y;
        sVertex1[2].pos[1] = y;
        sVertex1[3].pos[1] = y;
    } else {
        float x = mVideoAspect / surfaceAspect;
        sVertex1[0].pos[0] = -x;
        sVertex1[1].pos[0] = x;
        sVertex1[2].pos[0] = -x;
        sVertex1[3].pos[0] = x;
    }
}

void GLObjects::setPerspective(float aspect, float fovY, float zNear, float zFar) {
    float h2 = zNear * tanf(fovY);
    float w2 = h2 * aspect;
    LOGI("setPerspective l:%f, t:%f, r:%f, b:%f, zn:%f, zf:%f¥n",-w2, h2, w2, -h2, zNear, zFar);
    mProjection.perspective(-w2,  h2, w2, -h2, zNear, zFar);
}

void GLObjects::setImage(int width, int height, int bytesPerPixel, const uint8_t* data) {
    if (mTexture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTexture);
        switch (bytesPerPixel) {
            case 4:
                glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                break;
            case 2:
            {
                glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
                unsigned short* buf = new unsigned short[width * height];
                for (int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        unsigned short val = *((unsigned short*)(data + (x + y * width) * 2));
                        buf[x + y * width] = (val << 1) | 1;
                    }
                }
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB5_A1, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, buf);
                delete[] buf;
            } break;
            default:
                break;
        }
    }
}
