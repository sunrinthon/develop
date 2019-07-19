#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Text.h"
#include "Particle.h"

class UI :
	public Entity
{
public:
	UI();
	~UI();

	void update(float dt);
	bool checkWeapon(ItemType itemType);
	void weaponChange(ItemType itemType);
	void focusInventory(int i);
	void useItem();
	void addItem(ItemType itemType);

	list<Particle*> particleList;

	Sprite* frame;
	Sprite* inventory[10];
	Sprite* moneyIcon;
	Sprite* focus;
	Text* inventoryCount[10];
	Text* round;
	Text* money;
	int focusIndex;

	float trashTimer;
	float particleTimer;
	float particleTimerOrigin;
};

