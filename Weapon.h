#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Unit.h"

class Weapon :
	public Entity
{
public:
	Weapon(WeaponType type);
	~Weapon();

	void update(float dt);
	void attackUpdate();
	void changeState(State state);
	bool checkAttack(Unit* unit);

	Animation* attack;

	State state;
	WeaponType type;

	float attackDelay;
	float attackDelayOrigin;

	bool isAttacked;
	int damage;
	float attackRange;
};

