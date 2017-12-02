//
// Created by n-naka on 2017/01/22.
//

#ifndef Z_GLSHADER_H
#define Z_GLSHADER_H

#include <string>
#include "gl_lib.h"

struct ShaderName {
    std::string vs;
    std::string fs;
};

enum class Shader {
    SPRITE_SHADER = 0,
    COLOR_SHADER,
    TEXTURE_SHADER,
    SOBEL_SHADER,
#ifdef __ANDROID__
    VIDEO_TEXTURE_SHADER,
#endif
    SHADER_NUM
};

class GLShader {
private:
    GLuint mProgram;
    Shader mShader;
    
public:
    GLShader(GLuint prog, Shader s) : mProgram(prog), mShader(s) {
    }
    
    virtual ~GLShader() {
    }
    
    virtual void bind(const Matrix4f *mvp) {
        if (mProgram) {
            glUseProgram(mProgram);
            checkGlError("glUseProgram");
            
            if (mvp && is3D()) {
                GLuint id = glGetUniformLocation(mProgram,"mvp");
                glUniformMatrix4fv(id, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(mvp->v));
            }
        }
    }
    virtual void unbind() {
        if (mProgram) {
            glUseProgram(0);
        }
    }
    
    virtual void unload() {
        if (mProgram) {
            glDeleteProgram(mProgram);
        }
    }
    
    Shader getShader() const {
        return mShader;
    }
    
    GLuint getProgram() const {
        return mProgram;
    }
    
    virtual bool is3D() = 0;
};

#endif // Z_GLSHADER_H
