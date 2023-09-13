#include "Character.h"
#include "raymath.h"

Character::Character()
{
	width = 32.f;
	height = 32.f;
}

void Character::setScreenPos(int winWidth, int winHeight)
{
	screenPos = {
		(float)winWidth / 2.0f - 4.0f * (0.5f * (float)currentAnimation.texture.width),
		(float)winHeight / 2.0f - 4.0f * (0.5f * (float)currentAnimation.texture.height / currentAnimation.frames)
	};
}

void Character::tick(float deltaTime)
{
	worldPosLastFrame = worldPos;
	Vector2 direction{ };

	if (IsKeyDown(KEY_A)) direction.x -= 1.0;
	if (IsKeyDown(KEY_D)) direction.x += 1.0;
	if (IsKeyDown(KEY_W)) direction.y -= 1.0;
	if (IsKeyDown(KEY_S)) direction.y += 1.0;
	if (Vector2Length(direction) != 0.0)
	{
		currentAnimation = run;
		worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
		if (direction.x != 0)
			direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
	}
	else
	{
		currentAnimation = idle;
	}
	maxFrames = currentAnimation.frames;

	runningTime += deltaTime;
	if (runningTime >= updateTime)
	{
		frame++;
		runningTime = 0.f;
		frame %= maxFrames;
	}

	// Draw character
	Rectangle ballSource{
		0.0,
		frame * (float)idle.texture.height / 5.0f,
		rightLeft * (float)idle.texture.width,
		(float)idle.texture.height / 5.0f
	};
	Rectangle ballDest{
		screenPos.x,
		screenPos.y,
		4.0f * (float)idle.texture.width,
		4.0f * (float)idle.texture.height / 5.0f
	};
	Vector2 ballOrigin{ 0.0, 0.0 };
	DrawTexturePro(currentAnimation.texture, ballSource, ballDest, ballOrigin, 0.0, WHITE);
}

void Character::undoMovement()
{
	worldPos = worldPosLastFrame;
}