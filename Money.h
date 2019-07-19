#pragma once
#include "Entity.h"
#include "Sprite.h"

class Money :
	public Entity
{
public:
	Money();
	~Money();

	void update(float dt);

	Sprite* image;
	Vec2 targetPos;

	bool isFade;
};

