//
//  Constant2DShader.h
//  GameProto
//
//  Created by n-naka on 2017/09/23.
//  Copyright © 2017年 n-naka. All rights reserved.
//

#ifndef SpriteShader_h
#define SpriteShader_h

#include <string>
#include "ShaderAttribDef.h"

namespace SpriteShader {
    static auto sVertexShader =
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
    
    static auto sFragmentShader =
    "#version 300 es\n"
    "precision mediump float;\n"
    "in vec4 vColor;\n"
    "in vec2 vUv;\n"
    "out vec4 outColor;\n"
    "void main() {\n"
    "    outColor = vColor;\n"
    "}\n";
    
    static std::string vs() {
        return std::string(sVertexShader);
    }
    
    static std::string fs() {
        return std::string(sFragmentShader);
    }
};


#endif /* SpriteShader_h */
