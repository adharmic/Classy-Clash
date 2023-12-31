#pragma once
#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:

	Vector2 getWorldPos()
	{
		return worldPos;
	}

	Character(int winWidth, int winHeight);
	virtual void tick(float deltaTime) override;
	virtual Vector2 getScreenPos() override;
	Rectangle getWeaponCollisionRec() const { return weaponCollisionRec; }
	float getHealth() const { return health; }
	void takeDamage(const float& damage);
private:
	int windowWidth{ };
	int windowHeight{ };
	Texture2D weapon{ LoadTexture("characters/weapon_sword.png") };
	Rectangle weaponCollisionRec{ };
	float health{ 100.f };
};