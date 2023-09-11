#include "raylib.h"
#include "raymath.h"

int main()
{
	const int windowDimensions[2]{ 384, 384 };

	InitWindow(windowDimensions[0], windowDimensions[1], "Classy Clash");
	SetTargetFPS(60);

	Texture2D mapTexture = LoadTexture("tileset/classy_clash.png");
	Vector2 mapPos{ 0.0, 0.0 };

	const float moveSpeed{ 5.0f };

	// Frame data for various animations
	const float maxFramesIdle{ 5.f };
	const float maxFramesRun{ 8.f };

	Texture2D ballAndChain;

	Texture2D bCIdle = LoadTexture("characters/enemy/idle.png");
	Vector2 bCPosIdle{
		(float)windowDimensions[0] / 2.0f - 4.0f * (0.5f * (float)bCIdle.width),
		(float)windowDimensions[1] / 2.0f - 4.0f * (0.5f * (float)bCIdle.height / maxFramesIdle)
	};

	Texture2D bCRun = LoadTexture("characters/enemy/run.png");
	Vector2 bcPosRun{
		(float)windowDimensions[0] / 2.0f - 4.0f * (0.5f * (float)bCIdle.width),
		(float)windowDimensions[1] / 2.0f - 4.0f * (0.5f * (float)bCIdle.height / maxFramesRun)
	};

	// 1 = facing right, -1 = facing left
	float rightLeft{ 1.f };

	// Animation variables
	float runningTime{ };
	int frame{ };
	int maxFrames{ 5 };
	const float updateTime{ 1.f / 12.f };

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		Vector2 direction{ };

		if (IsKeyDown(KEY_A)) direction.x -= 1.0;
		if (IsKeyDown(KEY_D)) direction.x += 1.0;
		if (IsKeyDown(KEY_W)) direction.y -= 1.0;
		if (IsKeyDown(KEY_S)) direction.y += 1.0;
		if (Vector2Length(direction) != 0.0)
		{
			ballAndChain = bCRun;
			maxFrames = maxFramesRun;
			mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), moveSpeed));
			if (direction.x != 0)
				direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
		}
		else
		{
			ballAndChain = bCIdle;
			maxFrames = maxFramesIdle;
		}

		DrawTextureEx(mapTexture, mapPos, 0.0, 4.0, WHITE);

		// Update animation frame
		runningTime += GetFrameTime();
		if (runningTime >= updateTime)
		{
			frame++;
			runningTime = 0.f;
			frame %= maxFrames;
		}

		// Draw character
		Rectangle ballSource{
			0.0,
			frame * (float)bCIdle.height / 5.0f,
			rightLeft * (float)bCIdle.width,
			(float)bCIdle.height / 5.0f
		};
		Rectangle ballDest{
			bCPosIdle.x,
			bCPosIdle.y,
			4.0f * (float)bCIdle.width,
			4.0f * (float)bCIdle.height / 5.0f
		};
		Vector2 ballOrigin{ 0.0, 0.0 };
		DrawTexturePro(ballAndChain, ballSource, ballDest, ballOrigin, 0.0, WHITE);

		EndDrawing();
	}
	UnloadTexture(bCIdle);
	UnloadTexture(mapTexture);
	CloseWindow();
}