#pragma once
#include "Character.h"

class Enemy :
	public Character
{
public:
	Enemy(EnemyType type);
	~Enemy();

	void render();
	void update(float dt);

	void attackUpdate(float dt);
	void dieUpdate(float dt);
	void moveUpdate(float dt);
	void decreaseHp(int damage);

	Unit* target;

	Sprite* bar;
	Sprite* frame;

	EnemyType type;

	float attackDelay;
	float attackDelayOrigin;
	float damage;

	bool isLeft;
};