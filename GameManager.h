#pragma once
#include "GameScene.h"
#include "Bitmap.h"

struct InventoryItem
{
	ItemType type;
	int count;
};

class GameManager
{
public:
	GameManager();
	~GameManager();

	GameScene* ingame;
	Bitmap* bitmap;
	UI* ui;
	InventoryItem inventory[10];

	float goldChance;
	float ironChance;

	float crossbowChance;

	int round;
	int money;
};

extern GameManager gm;