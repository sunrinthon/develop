#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Unit.h"

class Item :
	public Entity
{
public:
	Item(ItemType type);
	~Item();

	void update(float dt);

	Sprite* sprite;
	ItemType type;
	Unit* followTarget;

	float gravity;
	bool onAir;
	float jumpSpeed;
	float speed;

	float deleteTimer;
	float deleteTimerOrigin;
};

