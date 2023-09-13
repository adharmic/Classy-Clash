#include "raylib.h"
#pragma once

struct Anim
{
	Texture2D texture;
	int frames;
};

class Character
{
public:

	Vector2 getWorldPos()
	{
		return worldPos;
	}

	Character();
	void setScreenPos(int winWidth, int winHeight);
	void tick(float deltaTime);
	void undoMovement();

private:
	Anim currentAnimation{ LoadTexture("characters/enemy/idle.png"), 5 };
	Anim idle{ LoadTexture("characters/enemy/idle.png"), 5 };
	Anim run{ LoadTexture("characters/enemy/run.png"), 8 };
	Vector2 screenPos{ };
	Vector2 worldPos{ 100.f, 200.f };
	float rightLeft{ 1.f };
	int frame{ };
	int maxFrames{ 5 };
	float runningTime{ };
	const float updateTime{ 1.f / 12.f };
	const float speed{ 4.f };
	float width{ };
	float height{ };
	Vector2 worldPosLastFrame{ };
};