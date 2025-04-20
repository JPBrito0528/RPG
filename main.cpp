#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main()
{
    // initiate window;
    int windowWidth = 384;
    int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "Neo RPG");

    // initiate neo map
    Texture2D neoMap = LoadTexture("Nature_tileset/natureMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale = 4.f;
    Character nakedMan{windowWidth, windowHeight};

    Prop rock{Vector2{0.f,0.f}, LoadTexture("nature_tileset/Rock.png")};


        // initate FPS
        SetTargetFPS(60);

    // Game
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground({191, 4, 4, 255});

        mapPos = Vector2Scale(nakedMan.getWorldPos(), -1.f);

        DrawTextureEx(neoMap, mapPos, 0.0, mapScale, WHITE);

        rock.Render(nakedMan.getWorldPos());

        nakedMan.tick(GetFrameTime(), windowWidth, windowHeight);

        if (nakedMan.getWorldPos().x < 0.f||
            nakedMan.getWorldPos().y < 0.f ||
            nakedMan.getWorldPos().x > neoMap.width * mapScale - windowWidth ||
            nakedMan.getWorldPos().y > neoMap.height * mapScale - windowHeight)
        {
            nakedMan.undoMovement();
        }

        EndDrawing();
    }
    UnloadTexture(neoMap);

    CloseWindow();
}