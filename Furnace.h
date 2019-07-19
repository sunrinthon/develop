#pragma once
#include "Object.h"

class Furnace :
	public Object
{
public:
	Furnace();
	~Furnace();

	void update(float dt);
	void smelt(WeaponType smeltItem);

	Animation* idle;
	Sprite* bar;
	Sprite* frame;

	WeaponType smeltItem;

	float smeltTimer;
	float smeltTimerOrigin;

	bool isSmelting;
};

