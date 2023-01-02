#pragma once
#include "pch.h"
#include "TileGrid.h"

const int tileWidth = 200;
const int tileHeight = 120;
const int tileThickness = 70;

struct TribeData {
    Tribes type;
    const char* name;
    std::map<TileTypes, Texture2D> tileSkins;
};

struct GameInstance {
    TileGrid bottom;
    TileGrid top;
};

class GameScreen {
public:
    RenderTexture2D renderTarget;
    GameInstance game;
    Cam cam;

    void Load();
    void Initialize();
    void Update();
    void Draw();
    void Unload();

    Rectangle GetCurrentViewPort();
    
private:
    int currentSW;
    int currentSH;

    void UpdateRenderTarget(bool reset=false);
};

Vector2 toScreenPos(Vector2 pos, int level=0);
Vector2 toWorldPos(Vector2 pos, Cam cam);
