#include "DXUT.h"
#include "Unit.h"


Unit::Unit(UnitType unitType): unitType(unitType), state(IDLE)
{
}


Unit::~Unit()
{
}


void Unit::decreaseHp(int damage)
{
	hp -= damage;
	
	if (hp < 0)
	{
		hp = 0;
	}
}