#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}


void BaseCharacter::undoMovement()
{
	worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
	return Rectangle
	{
		getScreenPos().x,
		getScreenPos().y,
		width * scale,
		height * scale
	};
}

void BaseCharacter::tick(float deltaTime)
{
	worldPosLastFrame = worldPos;

	runningTime += deltaTime;
	if (runningTime >= updateTime)
	{
		frame++;
		runningTime = 0.f;
		frame %= maxFrames;
	}

	if (Vector2Length(velocity) != 0.0)
	{
		texture = run;
		worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
		if (velocity.x != 0)
			velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
	}
	else
	{
		texture = idle;
	}
	velocity = { };

	// Draw character
	Rectangle source{
		width * frame,
		0.f,
		rightLeft * width,
		height
	};
	Rectangle dest{
		getScreenPos().x,
		getScreenPos().y,
		scale * width,
		scale * height
	};
	Vector2 origin{ 0.0, 0.0 };
	DrawTexturePro(texture, source, dest, origin, 0.0, WHITE);
}