#include "Textures.h"

std::map<Textures, const char*> texturePaths = {
    
};

std::map<Sounds, const char*> soundPaths = {

};

std::map<Shaders, const char*> shaderPaths = {

};

std::map<Textures, Texture2D> loadedTextures;
std::map<Sounds, Sound> loadedSounds;
std::map<Shaders, Shader> loadedShaders;

void LoadAssets() {
    for (auto &[name, path] : texturePaths) {
        loadedTextures[name] = LoadTexture(path);
        SetTextureFilter(loadedTextures[name], TEXTURE_FILTER_BILINEAR);
    }
    
    for (auto &[name, path] : soundPaths) {
        loadedSounds[name] = LoadSound(path);
    }
    
    for (auto &[name, path] : shaderPaths) {
        loadedShaders[name] = LoadShader(0, TextFormat(path, GLSL_VERSION));
    }
}

void UnloadAssets() {
    for (auto &[name, texture] : loadedTextures) {
        UnloadTexture(texture);
    }
    
    for (auto &[name, sound] : loadedSounds) {
        UnloadSound(sound);
    }
    
    for (auto &[name, shader] : loadedShaders) {
        UnloadShader(shader);
    }
}

Texture2D &GetTexture(Textures texture) {
    return loadedTextures.at(texture);
}

Sound &GetSound(Sounds sound) {
    return loadedSounds.at(sound);
}

Shader &GetShader(Shaders shader) {
    return loadedShaders.at(shader);
}