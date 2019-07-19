#include "DXUT.h"
#include "GameManager.h"


GameManager::GameManager()
{
	for (int i = 0; i < 10; i++)
	{
		inventory[i].type = NONE;
		inventory[i].count = 0;
	}

	inventory[0] = { ITEM_PICKAXE, 1 };
	inventory[1] = { ITEM_WOODEN_SWORD, 1 };
	inventory[2] = { ITEM_STONE_KEY, 1 };

	goldChance = 0.2;
	ironChance = 0.4;

	round = 0;
	money = 0;
}


GameManager::~GameManager()
{
}

GameManager gm;