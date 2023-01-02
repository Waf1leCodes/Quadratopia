#pragma once

struct TribeData;

enum Tribes {
    Neutral,
    Imperius
};

enum TileTypes {
    None,
    Ground,
    Mountain
};

struct Cam {
    Vector2 scroll;
    float zoom;
};

struct Tile {
    TileTypes type = TileTypes::None;
    Tribes tribe = Tribes::Neutral;
};

class TileGrid {
public:
    int width;
    int height;
    std::vector<Tile> values;

    TileGrid() = default;
    TileGrid(int _width, int _height);

    void SetAt(int x, int y, Tile newValue);
    Tile &GetAt(int x, int y);
    int IndexAt(int x, int y);
    bool IsOnGrid(int x, int y);

    void Render(std::map<Tribes, TribeData> &tribes, Rectangle viewport, int level=0);
};
