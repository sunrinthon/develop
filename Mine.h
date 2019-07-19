#pragma once
#include "Object.h"
class Mine :
	public Object
{
public:
	Mine();
	~Mine();


	void decreaseHp(int damage);

	Sprite* sprite;
	Sprite* bar;
	Sprite* frame;
};