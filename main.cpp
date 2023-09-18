#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>


int main()
{

	const int windowDimensions[2]{ 384, 384 };
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

	Character player{ windowDimensions[0], windowDimensions[1] };

	int score = 0;

	Prop props[2]
	{
		Prop{ Vector2{ 400.f, 400.f }, LoadTexture("tileset/Rock.png") },
		Prop{ Vector2{ 500.f, 400.f }, LoadTexture("tileset/Log.png") }
	};

	Enemy goblin
	{
		Vector2{ 600.f, 600.f },
		LoadTexture("characters/goblin_idle_spritesheet.png"),
		LoadTexture("characters/goblin_run_spritesheet.png")

	};

	const int numEnemies = 3;

	Enemy enemies[numEnemies]
	{
		Enemy
		{
			Vector2{ 600.f, 600.f },
			LoadTexture("characters/goblin_idle_spritesheet.png"),
			LoadTexture("characters/goblin_run_spritesheet.png")
		},
		Enemy
		{
			Vector2{ 1500.f, 1500.f },
			LoadTexture("characters/goblin_idle_spritesheet.png"),
			LoadTexture("characters/goblin_run_spritesheet.png")
		},
		Enemy
		{
			Vector2{ 3500.f, 1500.f },
			LoadTexture("characters/slime_idle_spritesheet.png"),
			LoadTexture("characters/slime_run_spritesheet.png")
		},
	};

	for (Enemy& enem : enemies)
	{
		enem.setTarget(&player);
	}

	int enemiesAlive = numEnemies;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		// Move and draw map
		mapPos = Vector2Scale(player.getWorldPos(), -1.f);
		DrawTextureEx(mapTexture, mapPos, 0.0, mapScale, WHITE);


		// Draw props
		for (Prop p : props)
		{
			p.Render(player.getWorldPos());
		}

		if (!player.getAlive())
		{
			DrawText("Game Over!", 55.f, 45.f, 40, RED);
			EndDrawing();
			continue;
		}
		else if (enemiesAlive <= 0)
		{

			DrawText("You Win!", 55.f, 45.f, 40, GREEN);
			EndDrawing();
			continue;
		}
		else
		{
			std::string playerHealth = "Health: ";
			playerHealth.append(std::to_string(player.getHealth()), 0, 5);
			DrawText(playerHealth.c_str(), 55.f, 45.f, 40, RED);

			std::string scoreText = "Score: ";
			scoreText.append(std::to_string(score), 0, 20);
			DrawText(scoreText.c_str(), 55.f, 5.f, 40, WHITE);
		}

		// Handle map boundary collision, draw player character, handle input
		player.tick(GetFrameTime());
		if (player.getWorldPos().x < 0.f ||
			player.getWorldPos().y < 150.f ||
			player.getWorldPos().x + windowDimensions[0] > mapTexture.width * mapScale ||
			player.getWorldPos().y + windowDimensions[1] + 230.f > mapTexture.height * mapScale)
		{
			player.undoMovement();
		}

		// Check player collision with props
		for (Prop p : props)
		{
			if (CheckCollisionRecs(p.GetCollisionRec(player.getWorldPos()), player.GetCollisionRec()))
			{
				player.undoMovement();
			}
		}
		
		for (Enemy& enem : enemies)
		{
			enem.tick(GetFrameTime());
		}

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{

			for (Enemy& enem : enemies)
			{
				if (CheckCollisionRecs(player.getWeaponCollisionRec(), enem.GetCollisionRec()))
				{
					// Apply damage
					enem.setAlive(false);
					enemiesAlive--;
					score += 100;
				}
			}
		}

		EndDrawing();
	}
	UnloadTexture(mapTexture);
	CloseWindow();
}