#include "Character.h"
#include "raymath.h"

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {(float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
                 (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)
    };
}


void Character::tick(float deltaTime, int winWidth, int winHeight)
{
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1;
    if (IsKeyDown(KEY_D))
        direction.x += 1;
    if (IsKeyDown(KEY_W))
        direction.y -= 1;
    if (IsKeyDown(KEY_S))
        direction.y += 1;
    if (Vector2Length(direction) != 0)
    {
        // set mapPos = mapPos - direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        rightLeft = direction.x < 0 ? -1.0f : 1.0f;

        // Update texture based on movement
        if (direction.x != 0)
        {
            texture = walkSide;
            blks = 4;
            i = 0;
        }
        else if (direction.y > 0)
        {
            texture = walkDown;
            blks = 3;
            i = 1;
        }
        else if (direction.y < 0)
        {
            texture = walkUp;
            blks = 4;
            i = 1;
        }
    }
    else
    {
        if (i == 0)
        {
            texture = idleSide; // Idle texture when no key is pressed
            blks = 4;
        }
        if (i == 1)
        {
            texture = idleFront; // Idle texture when no key is pressed
            blks = 5;
        }
    }
    Vector2 screenPos{
        winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / blks),
        winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)};

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    // draw character
    Rectangle source{frame * (float)texture.width / blks, 0.0f, rightLeft * (float)texture.width / blks, (float)texture.height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * (float)texture.width / blks, 4.0f * (float)texture.height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}