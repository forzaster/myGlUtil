//
//  SobelShader.h
//  GameProto
//
//  Created by n-naka on 2017/12/03.
//  Copyright © 2017年 forzaster. All rights reserved.
//

#ifndef SobelShader_h
#define SobelShader_h


#include <string>
#include "ShaderAttribDef.h"
#include "GLShader.h"

class SobelShader : public GLShader {
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
    "    vec4 c00 = textureOffset(tex, vUv, ivec2(-1,-1));\n"
    "    vec4 c10 = textureOffset(tex, vUv, ivec2( 0,-1));\n"
    "    vec4 c20 = textureOffset(tex, vUv, ivec2( 1,-1));\n"
    "    vec4 c01 = textureOffset(tex, vUv, ivec2(-1, 0));\n"
    "    vec4 c21 = textureOffset(tex, vUv, ivec2( 1, 0));\n"
    "    vec4 c02 = textureOffset(tex, vUv, ivec2(-1, 1));\n"
    "    vec4 c12 = textureOffset(tex, vUv, ivec2( 0, 1));\n"
    "    vec4 c22 = textureOffset(tex, vUv, ivec2( 1, 1));\n"
    "    vec4 dx = -c00 + c20 - c01 * 2.0 + c21 * 2.0 - c02 + c22;\n"
    "    vec4 dy = -c00 + c02 - c10 * 2.0 + c12 * 2.0 - c20 + c22;\n"
    "    vec4 c = vec4(1.0, 1.0, 1.0, 1.0) - sqrt(dx * dx + dy * dy) * 0.5;\n"
    "    outColor = vec4(c.yzw, 1.0f);\n"
    "}\n";

    static std::string vs() {
        return std::string(sVertexShader);
    }

    static std::string fs() {
        return std::string(sFragmentShader);
    }

    SobelShader(GLuint prog, Shader s) : GLShader(prog, s) {
    }

    virtual bool is3D() {
        return true;
    }
};

#endif /* SobelShader_h */
