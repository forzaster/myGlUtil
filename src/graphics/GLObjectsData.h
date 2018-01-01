//
// Created by n-naka on 2017/01/22.
//

#ifndef Z_GLOBJECTSDATA_H
#define Z_GLOBJECTSDATA_H

#include "../math/GLVector3.h"
#include "GLShader.h"
#include "Vertex.h"

struct Mesh {
    Vector3f posInWorld;
    const Vertex* vertex;
    int vertexSize;
    Shader shader;
};

static Vertex sVertex1[] = {
    {{-1.0f, -1.0f, 0.0f}, {0x00, 0xFF, 0x00}, {0.0f, 1.0f}},
    {{ 1.0f, -1.0f, 0.0f}, {0x00, 0x00, 0xFF}, {1.0f, 1.0f}},
    {{-1.0f,  1.0f, 0.0f}, {0xFF, 0x00, 0x00}, {0.0f, 0.0f}},
    {{ 1.0f,  1.0f, 0.0f}, {0xFF, 0xFF, 0xFF}, {1.0f, 0.0f}},
};

static Vertex sVertex2[] = {
    {{-2.8f, -4.9f, 0.0f}, {0x00, 0xFF, 0x00}, {0.0f, 1.0f}},
    {{ 2.8f, -4.9f, 0.0f}, {0x00, 0x00, 0xFF}, {1.0f, 1.0f}},
    {{-2.8f,  4.9f, 0.0f}, {0xFF, 0x00, 0x00}, {0.0f, 0.0f}},
    {{ 2.8f,  4.9f, 0.0f}, {0xFF, 0xFF, 0xFF}, {1.0f, 0.0f}},
};

static const Mesh sMeshes[] = {
#ifdef TARGET_OS_IPHONE
    {{0.0f, 0.0f, 0.0f}, sVertex1, sizeof(sVertex1) / sizeof(Vertex), Shader::SPRITE_SHADER},
//    {{0.0f, 0.0f, -10.0f}, sVertex2, sizeof(sVertex2) / sizeof(Vertex), Shader::TEXTURE_SHADER}
    {{0.0f, 0.0f, -10.0f}, sVertex2, sizeof(sVertex2) / sizeof(Vertex), Shader::SOBEL_SHADER}
#else
    {{0.0f, 0.0f, 0.0f}, sVertex1, sizeof(sVertex1) / sizeof(Vertex), Shader::VIDEO_TEXTURE_SHADER},
//    {{0.0f, 0.0f, -10.0f}, sVertex2, sizeof(sVertex2) / sizeof(Vertex), Shader::COLOR_SHADER}
#endif
};

#endif //Z_GLOBJECTSDATA_H
