#include "pch.h"
#include "TileGrid.h"
#include "Textures.h"
#include "Game.h"
#include "debug.h"
#include "utils.h"

TileGrid::TileGrid(int _width, int _height) {
    width = _width;
    height = _height;
    values = std::vector<Tile>(width * height, Tile {});
}

void TileGrid::SetAt(int x, int y, Tile newValue) {
    if (!IsOnGrid(x, y)) return;
    
    values[IndexAt(x, y)] = newValue;
}

Tile &TileGrid::GetAt(int x, int y) {
    return values[IndexAt(x, y)];
}

int TileGrid::IndexAt(int x, int y) {
    return y * width + x;
}

bool TileGrid::IsOnGrid(int x, int y) {
    return x >= 0 && y >= 0 && x < width && y < height;
}

void TileGrid::Render(std::map<Tribes, TribeData> &tribes, Rectangle viewport, Vector2 screenSize, int level) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Tile &tile = GetAt(x, y);
            if (tile.type == TileTypes::None) continue;

            Texture2D &texture = tribes[tile.tribe].tileSkins[tile.type];
            Vector2 screenPos = toScreenPos({(float) x, (float) y}, level);
            Rectangle dest = {screenPos.x + width * tileWidth / 2, screenPos.y, (float) texture.width, (float) texture.height};

            if (CheckCollisionRecs(viewport, dest) && CheckCollisionRecs({0, 0, screenSize.x, screenSize.y}, dest)) {
                DrawTexturePro(texture, {0, 0, (float) texture.width, (float) texture.height}, dest, {0, 0}, 0, WHITE);
            }
        }
    }
}