#include "pch.h"
#include "Application.h"

int main() {
    Application* app = new Application();

    app->Load();
    app->Start();
    app->Unload();

    delete app;
    return 0;
}