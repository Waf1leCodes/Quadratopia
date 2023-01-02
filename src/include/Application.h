#pragma once
#include "Game.h"

enum ApplicationStates {
    Running
};

class Application {
public:
    int initialSW = 1080;
    int initialSH = 720;
    ApplicationStates appState;

    GameScreen gameScreen;

    void Load();
    void Start();
    void Unload();
};