//
// Created by n-naka on 2017/01/22.
//

#ifndef Z_GLOBJECTSDATA_H
#define Z_GLOBJECTSDATA_H

#include <string>

#include "Vertex.h"
#include "Constant2DShader.h"
#include "VideoTextureShader.h"

enum class Shader {
#ifdef IOS
    CONSTANT_2D_SHADER = 0,
#else
    VIDEO_TEXTURE_SHADER = 0,
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
#ifdef IOS
    {Constant2DShader::vs(), Constant2DShader::fs()},
#else
    {VideoTextureShader::vs(), VideoTextureShader::fs()},
#endif
};

static Vertex sVertex1[] = {
    {{-1.0f, -1.0f}, {0x00, 0xFF, 0x00}, {0.0f, 1.0f}},
    {{ 1.0f, -1.0f}, {0x00, 0x00, 0xFF}, {1.0f, 1.0f}},
    {{-1.0f,  1.0f}, {0xFF, 0x00, 0x00}, {0.0f, 0.0f}},
    {{ 1.0f,  1.0f}, {0xFF, 0xFF, 0xFF}, {1.0f, 0.0f}},
};

static const Mesh sMeshes[] = {
#ifdef IOS
    {sVertex1, sizeof(sVertex1) / sizeof(Vertex), Shader::CONSTANT_2D_SHADER}
#else
    {sVertex1, sizeof(sVertex1) / sizeof(Vertex), Shader::VIDEO_TEXTURE_SHADER}
#endif
};

#endif //Z_GLOBJECTSDATA_H
