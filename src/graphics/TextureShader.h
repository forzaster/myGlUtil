//
//  TextureShader.h
//  GameProto
//
//  Created by n-naka on 2017/11/19.
//  Copyright © 2017年 forzaster. All rights reserved.
//

#ifndef TextureShader_h
#define TextureShader_h

#include <string>
#include "ShaderAttribDef.h"
#include "GLShader.h"

class TextureShader : public GLShader {
public:
    constexpr static auto sVertexShader =
    "#version 300 es\n"
    "layout(location=" STRV(POS_ATTRIB) ") in vec3 pos;\n"
    "layout(location=" STRV(COLOR_ATTRIB) ") in vec4 color;\n"
    "layout(location=" STRV(UV_ATTRIB) ") in vec2 uv;\n"
    "uniform mat4 mvp;\n"
    "out vec4 vColor;\n"
    "out vec2 vUv;\n"
    "void main() {\n"
    "    gl_Position = mvp * vec4(pos, 1.0);\n"
    "    vColor = color;\n"
    "    vUv = uv;\n"
    "}\n";
    
    constexpr static auto sFragmentShader =
    "#version 300 es\n"
    "precision mediump float;\n"
    "uniform sampler2D tex;\n"
    "in vec4 vColor;\n"
    "in vec2 vUv;\n"
    "out vec4 outColor;\n"
    "void main() {\n"
    "    vec4 c = texture(tex, vUv);\n"
    "    outColor = vec4(c.yzw, 1.0f);\n"
    "}\n";
    
    static std::string vs() {
        return std::string(sVertexShader);
    }
    
    static std::string fs() {
        return std::string(sFragmentShader);
    }
    
    TextureShader(GLuint prog, Shader s) : GLShader(prog, s) {
    }
    
    virtual bool is3D() {
        return true;
    }
};

#endif /* TextureShader_h */
