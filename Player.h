#pragma once
#include "Character.h"
#include "Sprite.h"
#include "Weapon.h"

class Player :
	public Character
{
public:
	Player();
	~Player();

	void render();
	void update(float dt);
	void colUpdate(float dt);
	void moveUpdate(float dt);
	void jumpUpdate(float dt);
	void dieUpdate(float dt);
	void changeWeapon(WeaponType weaponType);
	void decreaseHp(int damage);

	Weapon* weapon;
	Sprite* bar;
	Sprite* frame;

	Vec2 lastPos;
	bool onAir;
	bool isJump;

	float gravity;
	float jumpSpeed;
	float particleTimer;
	float rebornTimer;

	bool isDead;
};

