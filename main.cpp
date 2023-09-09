#include "raylib.h"

int main()
{
	const int windowDimensions[2]{ 384, 384 };

	InitWindow(windowDimensions[0], windowDimensions[1], "Classy Clash");

	Texture2D mapTexture = LoadTexture("tileset/classy_clash.png");
	Vector2 bgPos{ 0, 0 };

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		DrawTextureEx(mapTexture, bgPos, 0, 4.0, WHITE);

		EndDrawing();
	}

	UnloadTexture(mapTexture);
}