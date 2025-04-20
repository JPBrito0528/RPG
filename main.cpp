#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    // initiate window;
    int windowWidth = 1920;
    int windowHeight = 1080;
    InitWindow(windowWidth, windowHeight, "Neo RPG");

    // initiate neo map
    Texture2D neoMap = LoadTexture("Neo RPG/Neo.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale = 4.f;
    Character nakedMan{windowWidth, windowHeight};

        // initate FPS
        SetTargetFPS(60);

    // Game
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground({191, 4, 4, 255});

        mapPos = Vector2Scale(nakedMan.getWorldPos(), -1.f);

        DrawTextureEx(neoMap, mapPos, 0.0, mapScale, WHITE);
        nakedMan.tick(GetFrameTime(), windowWidth, windowHeight);

        if (nakedMan.getWorldPos().x < -windowWidth/2 ||
            nakedMan.getWorldPos().y < 0.f ||
            nakedMan.getWorldPos().x > neoMap.width * mapScale - windowWidth/2 ||
            nakedMan.getWorldPos().y > neoMap.height * mapScale - windowHeight/2)
        {
            nakedMan.undoMovement();
        }

        EndDrawing();
    }
    UnloadTexture(neoMap);

    CloseWindow();
}