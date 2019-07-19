#pragma once
#include "Entity.h"
#include "Animation.h"

class Unit :
	public Entity
{
public:
	Unit(UnitType unitType);
	~Unit();

	virtual void decreaseHp(int damage);

	Team team;
	UnitType unitType;
	State state;
	int hp;
	int hpOrigin;
};

