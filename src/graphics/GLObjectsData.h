//
// Created by n-naka on 2017/01/22.
//

#ifndef Z_GLOBJECTSDATA_H
#define Z_GLOBJECTSDATA_H

#include <string>
#include "gl_lib.h"

#include "Vertex.h"
#include "Constant2DShader.h"
#include "ConstantShader.h"
#include "VideoTextureShader.h"

enum class Shader {
    CONSTANT_2D_SHADER = 0,
    CONSTANT_SHADER,
#ifdef __ANDROID__
    VIDEO_TEXTURE_SHADER,
#endif
    SHADER_NUM
};

struct ShaderName {
    std::string vs;
    std::string fs;
};

struct Mesh {
    const Vertex* vertex;
    int vertexSize;
    Shader shader;
};

static const ShaderName sShaderName[] = {
    {Constant2DShader::vs(), Constant2DShader::fs()},
    {ConstantShader::vs(), ConstantShader::fs()},
#ifdef __ANDROID__
    {VideoTextureShader::vs(), VideoTextureShader::fs()},
#endif
};

static Vertex sVertex1[] = {
    {{-1.0f, -1.0f, 0.0f}, {0x00, 0xFF, 0x00}, {0.0f, 1.0f}},
    {{ 1.0f, -1.0f, 0.0f}, {0x00, 0x00, 0xFF}, {1.0f, 1.0f}},
    {{-1.0f,  1.0f, 0.0f}, {0xFF, 0x00, 0x00}, {0.0f, 0.0f}},
    {{ 1.0f,  1.0f, 0.0f}, {0xFF, 0xFF, 0xFF}, {1.0f, 0.0f}},
};

static const Mesh sMeshes[] = {
#ifdef TARGET_OS_IPHONE
    {sVertex1, sizeof(sVertex1) / sizeof(Vertex), Shader::CONSTANT_2D_SHADER}
#else
    {sVertex1, sizeof(sVertex1) / sizeof(Vertex), Shader::VIDEO_TEXTURE_SHADER}
#endif
};

#endif //Z_GLOBJECTSDATA_H
