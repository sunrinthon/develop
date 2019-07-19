#pragma once
#include "Unit.h"
class Object :
	public Unit
{
public:
	Object(UnitType unitType);
	~Object();
};

