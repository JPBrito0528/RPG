#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Stephen's Top Down");

    Texture2D map = LoadTexture("nature_tileset/natureMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{windowWidth, windowHeight};

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy goblin1{
        Vector2{200.f, 400.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy goblin2{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy goblin3{
        Vector2{330.f, 960.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy goblin4{
        Vector2{400.f, 100.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy goblin5{
        Vector2{120.f, 220.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy *enemies[5];

    enemies[0] = &goblin1;
    enemies[1] = &goblin2;
    enemies[2] = &goblin3;
    enemies[3] = &goblin4;
    enemies[4] = &goblin5;

    for (auto enemy : enemies) // Loop over the array by index
    {
        enemy->setTarget(&knight); // Access the object using the pointer
    }

SetTargetFPS(60);
while (!WindowShouldClose())
{
    BeginDrawing();
    ClearBackground(WHITE);

    mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

    // draw the map
    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

    // draw the props
    for (auto prop : props)
    {
        prop.Render(knight.getWorldPos());
    }

    if (!knight.getAlive())
    {
        DrawText("Game Over!", 55.f, 45.f, 40, RED);
        EndDrawing();
        continue;
    }
    else
    {

        std::string knightHealth = "Health: ";
        knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
        DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
    }

    knight.tick(GetFrameTime());
    // check map bounds
    if (knight.getWorldPos().x < 0.f ||
        knight.getWorldPos().y < 0.f ||
        knight.getWorldPos().x + windowWidth > map.width * mapScale ||
        knight.getWorldPos().y + windowHeight > map.height * mapScale)
    {
        knight.undoMovement();
    }
    // check prop collisions
    for (auto prop : props)
    {
        if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
        {
            knight.undoMovement();
        }
    }

    for (auto enemy : enemies) // Loop over the array by index
    {
        enemy->tick(GetFrameTime()); // Access the object using the pointer
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getCollisionRec()))
            {
                enemy->setAlive(false);
            }
        }
    }

    EndDrawing();
}
CloseWindow();
}