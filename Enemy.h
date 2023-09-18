#pragma once
#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:

	Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
	virtual void tick(float deltaTime) override;
	void setTarget(Character* new_target) { target = new_target; }
	virtual Vector2 getScreenPos() override;
private:
	Character* target;
	float dps{ 10.f };
	float radius{ 25.f };
};