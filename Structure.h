#pragma once
#include "Object.h"
#include "Character.h"

class Structure :
	public Object
{
public:
	Structure(StructureType type);
	~Structure();

	void update(float dt);
	void render();
	void attackUpdate(float dt);
	void dieUpdate(float dt);
	void idleUpdate(float dt);
	void changeState(State state);
	void decreaseHp(int damage);

	Animation* play;
	Animation* idle;
	Animation* attack;

	Sprite* bar;
	Sprite* frame;

	StructureType type;

	Character* target;

	float attackDelay;
	float attackDelayOrigin;
	float attackRange;

	int damage;
};