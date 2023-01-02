#pragma once
#include "pch.h"

#if defined(PLATFORM_WEB)
    #define GLSL_VERSION    100
#else
    #define GLSL_VERSION    330
#endif

enum Textures {
    
};

enum Sounds {

};

enum Shaders {

};

void LoadAssets();
void UnloadAssets();

Texture2D &GetTexture(Textures texture);
Sound &GetSound(Sounds sound);
Shader &GetShader(Shaders shader);
