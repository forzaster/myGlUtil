//
// Created by n-naka on 2017/01/22.
//

#ifndef Z_GLOBJECTSDATA_H
#define Z_GLOBJECTSDATA_H

#include "GLShader.h"
#include "Vertex.h"

struct Mesh {
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
    {{-1.0f, -1.0f  , -10.0f}, {0x00, 0xFF, 0x00}, {0.0f, 1.0f}},
    {{ 1.0f, -1.0f, -50.0f}, {0x00, 0x00, 0xFF}, {1.0f, 1.0f}},
    {{-1.0f,  1.0f, -10.0f}, {0xFF, 0x00, 0x00}, {0.0f, 0.0f}},
    {{ 1.0f,  1.0f, -50.0f}, {0xFF, 0xFF, 0xFF}, {1.0f, 0.0f}},
};

static const Mesh sMeshes[] = {
#ifdef TARGET_OS_IPHONE
    {sVertex1, sizeof(sVertex1) / sizeof(Vertex), Shader::CONSTANT_2D_SHADER},
#else
    {sVertex1, sizeof(sVertex1) / sizeof(Vertex), Shader::VIDEO_TEXTURE_SHADER},
#endif
    {sVertex2, sizeof(sVertex2) / sizeof(Vertex), Shader::CONSTANT_SHADER}
};

#endif //Z_GLOBJECTSDATA_H
