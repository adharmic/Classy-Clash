#pragma once
#include "raylib.h"
class BaseCharacter
{
public:
	BaseCharacter();

	Vector2 getWorldPos()
	{
		return worldPos;
	}
	void undoMovement();
	Rectangle GetCollisionRec();
	virtual void tick(float deltaTime);
	virtual Vector2 getScreenPos() = 0;
	bool getAlive() { return alive; }
	void setAlive(const bool& isAlive) { alive = isAlive; }
protected:
	Texture2D texture{ LoadTexture("characters/knight_idle_spritesheet.png") };
	Texture2D idle{ LoadTexture("characters/knight_idle_spritesheet.png") };
	Texture2D run{ LoadTexture("characters/knight_run_spritesheet.png") };
	Vector2 worldPos{ 100.f, 200.f };
	Vector2 worldPosLastFrame{ };
	Vector2 velocity{ };
	float rightLeft{ 1.f };
	int frame{ };
	const int maxFrames{ 6 };
	float runningTime{ };
	const float updateTime{ 1.f / 12.f };
	float speed{ 4.f };
	float width{ };
	float height{ };
	float scale{ 4.f };
private:
	bool alive{ true };

};