#include "pch.h"
#include "Application.h"
#include "Textures.h"
#include "debug.h"

void Application::Load() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(initialSW, initialSH, "Quadratopia");
    LoadAssets();
    SetTargetFPS(60);

    gameScreen.Load();
    gameScreen.Initialize();
}

void Application::Unload() {
    CloseWindow();
    UnloadAssets();

    gameScreen.Unload();
}

void Application::Start() {
    while (!WindowShouldClose()) {
        
        // Update Frames
        switch (appState)
        {
        case ApplicationStates::Running:
            gameScreen.Update();
            break;
        
        default:
            break;
        }

        // // Draw Frames
        BeginDrawing();
            ClearBackground(BLACK);
            
            switch (appState)
            {
            case ApplicationStates::Running:
                gameScreen.Draw();
                break;
            
            default:
                break;
            }

        if (IsKeyDown(KEY_F))
            DrawFPS(10, 10);
            
        EndDrawing();
    }
}