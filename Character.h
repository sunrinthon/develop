#pragma once
#include "Unit.h"

class Character :
	public Unit
{
public:
	Character();
	~Character();

	void render();
	void update(float dt);

	virtual void moveUpdate(float dt) = 0;
	virtual void dieUpdate(float dt) = 0;
	void changeState(State state);

	Animation* play;
	Animation* idle;
	Animation* move;
	Animation* attack;

	float speed;
};

