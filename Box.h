#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Animation.h"

class Box :
	public Object
{
public:
	Box();
	~Box();

	void render();
	void update(float dt);
	void dieUpdate(float dt);
	void openBox(WeaponType weaponType);

	Animation* play;
	Animation* idle;
	Animation* open;

	Sprite* bar;
	Sprite* frame;

	ItemType addItem;

	bool isOpend;
	bool isDropped;
};

