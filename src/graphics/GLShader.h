//
// Created by n-naka on 2017/01/22.
//

#ifndef Z_GLSHADER_H
#define Z_GLSHADER_H

#include <string>

struct ShaderName {
    std::string vs;
    std::string fs;
};

enum class Shader {
    CONSTANT_2D_SHADER = 0,
    CONSTANT_SHADER,
#ifdef __ANDROID__
    VIDEO_TEXTURE_SHADER,
#endif
    SHADER_NUM
};

#endif // Z_GLSHADER_H
