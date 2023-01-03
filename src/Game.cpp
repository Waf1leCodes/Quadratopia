#include "pch.h"
#include "Textures.h"
#include "Game.h"
#include "Utils.h"
#include "debug.h"
#include "raymath.h"

bool isDragging;
Vector2 dragStart;
Vector2 dragVel;

const float minZoom = 0.4;
const float maxZoom = 2;

std::map<Tribes, TribeData> tribes;

void LoadTribe(Tribes tribe, const char* name);

void HandleMovement(Cam &cam);

void GameScreen::Load() {
    game.bottom = TileGrid(2, 2);
    game.top = TileGrid(4, 4);
    UpdateRenderTarget(true);

    LoadTribe(Tribes::Imperius, "Imperius");
}

void GameScreen::Initialize() {
    for (int x = 0; x < game.bottom.width; x++) {
        for (int y = 0; y < game.bottom.height; y++) {
            game.bottom.SetAt(x, y, Tile {TileTypes::Ground, Tribes::Imperius});
        }
    }

    for (int x = 0; x < game.top.width; x++) {
        for (int y = 0; y < game.top.height; y++) {
            if (GetRandomValue(0, 9) == 0)
                game.top.SetAt(x, y, Tile {TileTypes::Mountain, Tribes::Imperius});
        }
    }

    dragVel = {0, 0};
    cam.scroll = {0, 0};
    cam.zoom = 1;
}

void GameScreen::Update() {
    UpdateRenderTarget();
    HandleMovement(cam);
}

void GameScreen::Draw() {
    BeginTextureMode(renderTarget);
        ClearBackground(BLANK);
        DrawRectangle(0, 0, 250, 250, RED);
    EndTextureMode();

    Rectangle source = GetCurrentViewPort();

    if (source.x + source.width > renderTarget.texture.width)
        source.width -= (source.x + source.width) - renderTarget.texture.width;

    print(source.width);
    
    Rectangle dest = {0, 0, source.width * cam.zoom, (float) source.height * cam.zoom};
    DrawTexturePro(renderTarget.texture, {cam.scroll.x, -cam.scroll.y, source.width, -source.height}, dest, {0, 0}, 0, WHITE);
}

void GameScreen::Unload() {
    for (auto &[name, data] : tribes) {
        for (auto &[type, texture] : data.tileSkins) {
            UnloadTexture(texture);
        }
    }
}

Rectangle GameScreen::GetCurrentViewPort() {
    Rectangle viewport = {max(floor(cam.scroll.x), 0.0f), max(floor(cam.scroll.y), 0.0f), currentSW / cam.zoom, currentSH / cam.zoom};
    return viewport;
}

void GameScreen::UpdateRenderTarget(bool reset) {
    if (currentSW != GetScreenWidth() || currentSH != GetScreenHeight() || reset) {
        currentSW = GetScreenWidth();
        currentSH = GetScreenHeight();
        renderTarget = LoadRenderTexture(currentSW, currentSH);
        SetTextureFilter(renderTarget.texture, TEXTURE_FILTER_BILINEAR);
    }
}

/* ================ Update ================ */

void HandleMovement(Cam &cam) {
    Vector2 mp = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (!isDragging) {
            isDragging = true;
            dragStart = toWorldPos(mp, cam);
        }
        Vector2 difference = dragStart - toWorldPos(mp, cam);
        cam.scroll = cam.scroll + difference;

    } else {
        if (isDragging) {
            dragVel = (dragStart - toWorldPos(mp, cam)) / Vector2 {4, 4};
        }
        isDragging = false;
    }

    if (dragVel.x || dragVel.y) {
        cam.scroll = cam.scroll + dragVel;

        int dimValue = 1.5;
        if (abs(dragVel.x) < dimValue)
            dragVel.x = 0;
        else
            if (dragVel.x > 0)
                dragVel.x -= dimValue;
            else
                dragVel.x += dimValue;

        if (abs(dragVel.y) < dimValue)
            dragVel.y = 0;
        else
            if (dragVel.y > 0)
                dragVel.y -= dimValue;
            else
                dragVel.y += dimValue;
    }

    // Zooming
    int mouseWheelMove = GetMouseWheelMove();
    if (mouseWheelMove) {
        cam.zoom += 0.2 * mouseWheelMove;
        if (cam.zoom < minZoom)
            cam.zoom = minZoom;
        if (cam.zoom > maxZoom)
            cam.zoom = maxZoom;
    }
}

/* ================ Funcs ================ */

Vector2 toScreenPos(Vector2 pos, int level) {
    return {
        (pos.x - pos.y) * (tileWidth / 2), 
        (pos.x + pos.y) * (tileHeight / 2) - level * tileThickness
    };
}

Vector2 toWorldPos(Vector2 pos, Cam cam) {
    return {pos.x / cam.zoom + cam.scroll.x, pos.y / cam.zoom + cam.scroll.y};
}

void LoadTribe(Tribes tribe, const char* name) {
    TribeData &data = tribes[tribe];
    data.type = tribe;
    data.name = name;

    data.tileSkins[TileTypes::Ground] = LoadTexture(TextFormat("assets/Tribes/%s/%s ground.png", name, name));
    data.tileSkins[TileTypes::Mountain] = LoadTexture(TextFormat("assets/Tribes/%s/%s mountain.png", name, name));
    
    for (auto &[type, texture] : data.tileSkins) {
        SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
    }
}
