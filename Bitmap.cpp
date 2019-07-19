#include "DXUT.h"
#include "Bitmap.h"
#include "GameManager.h"

Bitmap::Bitmap()
{
	gm.bitmap = this;

	mapSprite = new Sprite("image/bit.png");
	addChild(mapSprite);
	mapSprite->color.a = 0;

	init();
}

Bitmap::~Bitmap()
{
	delete(mapBit);
}

void Bitmap::init()
{
	int spriteWidth = mapSprite->rect.right;
	int spriteHeight = mapSprite->rect.bottom;
	mapWidth = spriteWidth;
	mapHeight = spriteHeight;
	int totalBit = mapWidth * mapHeight;

	mapBit = new int[totalBit / 32 + ((totalBit % 32 > 0) ? 1 : 0)];
	ZeroMemory(mapBit, sizeof(int) * (totalBit / 32 + ((totalBit % 32 > 0) ? 1 : 0)));

	DWORD* data;
	D3DLOCKED_RECT lockRect;

	LPDIRECT3DSURFACE9 surface;
	mapSprite->texture->d3dTexture->GetSurfaceLevel(0, &surface);
	surface->LockRect(&lockRect, 0, 0);
	data = (DWORD*)lockRect.pBits;
	surface->UnlockRect();
	SAFE_RELEASE(surface);

	for (int j = 0; j < mapHeight; j++)
	{
		for (int k = 0; k < spriteWidth; k++)
		{
			int index = j * lockRect.Pitch / 4 + k;
			mapSetting(k, j, data[index]);
		}

	}
}

void Bitmap::mapSetting(int x, int y, D3DCOLOR color)
{
	if (color == D3DCOLOR_XRGB(0, 0, 0))
	{
		setBit(x, y, true);
	}
	else
	{
		//setBit(x, y, false);
	}
}

void Bitmap::setBit(int x, int y, bool b)
{
	if (x < 0 || x > mapWidth) return;
	if (y < 0 || y > mapHeight) return;

	int Pitch = y * mapWidth + x;
	mapBit[Pitch / 32] ^= (1 << Pitch % 32);
}

bool Bitmap::getBit(int x, int y)
{
	if (x < 0 || x > mapWidth) return false;
	if (y < 0 || y > mapHeight) return true;

	int Pitch = y * mapWidth + x;
	
	return mapBit[Pitch / 32] & (1 << Pitch % 32);
}
