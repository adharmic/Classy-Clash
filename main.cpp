#include "raylib.h"
#include "raymath.h"
#include "Character.h"

const int windowDimensions[2]{ 384, 384 };

int main()
{

	InitWindow(windowDimensions[0], windowDimensions[1], "Classy Clash");
	SetTargetFPS(60);

	Texture2D mapTexture = LoadTexture("tileset/classy_clash.png");
	Vector2 mapPos{ 0.0, 0.0 };

	const float mapScale{ 4.f };

	// Frame data for various animations
	const float maxFramesIdle{ 5.f };
	const float maxFramesRun{ 8.f };

	// 1 = facing right, -1 = facing left
	float rightLeft{ 1.f };

	// Animation variables
	float runningTime{ };
	int frame{ };
	int maxFrames{ 5 };
	const float updateTime{ 1.f / 12.f };

	Character player{ };
	player.setScreenPos(windowDimensions[0], windowDimensions[1]);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		mapPos = Vector2Scale(player.getWorldPos(), -1.f);

		DrawTextureEx(mapTexture, mapPos, 0.0, mapScale, WHITE);
		player.tick(GetFrameTime());
		if (player.getWorldPos().x < 0.f ||
			player.getWorldPos().y < 150.f ||
			player.getWorldPos().x + windowDimensions[0] > mapTexture.width * mapScale ||
			player.getWorldPos().y + windowDimensions[1] > mapTexture.height * mapScale)
		{
			player.undoMovement();
		}

		EndDrawing();
	}
	UnloadTexture(mapTexture);
	CloseWindow();
}