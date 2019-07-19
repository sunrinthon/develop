#include "DXUT.h"
#include "Character.h"


Character::Character() : Unit(CHARACTER)
{
	renderChildrenEnabled = false;
}


Character::~Character()
{
}

void Character::render()
{
	Unit::render();

	play->render();
}

void Character::update(float dt)
{
	play->update(dt);

	moveUpdate(dt);

	dieUpdate(dt);
}


void Character::changeState(State state)
{
	if (this->state == state) return;

	this->state = state;

	switch (state)
	{
	case IDLE:
		play = idle;
		break;
	case MOVE:
		play = move;
		break;
	case ATTACK:
		play = attack;
		break;
	case DIE:
		play = idle;
		break;
	default:
		break;
	}

	play->currentFrame = 0;
	play->update(0);
}