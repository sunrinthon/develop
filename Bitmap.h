#pragma once
#include "Entity.h"
#include "Sprite.h"

class Bitmap :
	public Entity
{
public:
	Bitmap();
	~Bitmap();

	void init();
	void mapSetting(int x, int y, D3DCOLOR color);
	void setBit(int x, int y, bool b);
	bool getBit(int x, int y);

	int mapWidth;
	int mapHeight;
	int* mapBit;

	Sprite* mapSprite;
};