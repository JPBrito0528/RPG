#include "raylib.h"

class Character
{
public:
    Character(int winWidth,int winHeight);
    Vector2 getWorldPos() { return worldPos; }
    void tick(float deltaTime, int winWidth, int winHeight);
    void undoMovement();

private:
    Texture2D texture{LoadTexture("nakedMan/SHEEFT/IDLE/idleFront.png")};
    Texture2D idleFront{LoadTexture("nakedMan/SHEEFT/IDLE/idleFront.png")};
    Texture2D idleSide{LoadTexture("nakedMan/SHEEFT/IDLE/idleSide.png")};
    Texture2D walkSide{LoadTexture("nakedMan/SHEEFT/WALK/walkSide.png")};
    Texture2D walkUp{LoadTexture("nakedMan/SHEEFT/WALK/walkUp.png")};
    Texture2D walkDown{LoadTexture("nakedMan/SHEEFT/WALK/walkDown.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    int blks{};
    int i{};
    float rightLeft = 1.f;
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float Scale{4.f};
};
