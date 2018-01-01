//
// Created by n-naka on 2017/01/09.
//

#ifndef Z_VIDEOTEXTURESHADER_H
#define Z_VIDEOTEXTURESHADER_H

#ifdef __ANDROID__
#include <string>
#include "ShaderAttribDef.h"
#include "GLShader.h"

class VideoTextureShader : public GLShader {
public:
    constexpr static auto sVertexShader =
            "#version 300 es\n"
                    "layout(location=" STRV(POS_ATTRIB) ") in vec3 pos;\n"
                    "layout(location=" STRV(COLOR_ATTRIB) ") in vec4 color;\n"
                    "layout(location=" STRV(UV_ATTRIB) ") in vec2 uv;\n"
                    "out vec4 vColor;\n"
                    "out vec2 vUv;\n"
                    "void main() {\n"
                    "    gl_Position = vec4(pos, 1.0);\n"
                    "    vColor = color;\n"
                    "    vUv = uv;\n"
                    "}\n";

    constexpr static auto sFragmentShader =
            "#version 300 es\n"
            "#extension GL_OES_EGL_image_external : require\n"
            "precision mediump float;\n"
            "uniform samplerExternalOES tex;\n"
            "in vec4 vColor;\n"
            "in vec2 vUv;\n"
            "out vec4 outColor;\n"
            "void main() {\n"
#ifdef SOBEL
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
#else
            "    outColor = texture(tex, vUv);\n"
#endif
            "}\n";

    static std::string vs() {
        return std::string(sVertexShader);
    }

    static std::string fs() {
        return std::string(sFragmentShader);
    }
    
    VideoTextureShader(GLuint prog, Shader s) : GLShader(prog, s) {
    }
    
    virtual bool is3D() {
        return false;
    }
};
#endif

#endif //Z_VIDEOTEXTURESHADER_H
