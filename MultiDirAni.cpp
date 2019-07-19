#include "DXUT.h"
#include "MultiDirAni.h"


MultiDirAni::MultiDirAni(string path, int frameNum, float fps, bool loop)
	:dir(0)
{
	for (int i = 0; i < 8; i++)
	{
		ani[i] = new Animation(path + "/" + to_string(i), frameNum, fps, loop);
	}
	texture = ani[0]->texture;

	rect = visibleRect = Rect(0, 0, texture->info.Width, texture->info.Height);
}

MultiDirAni::~MultiDirAni()
{
	for (int i = 0; i < 8; i++)
	{
		SAFE_DELETE(ani[i]);
	}
}

void MultiDirAni::update(float dt)
{
	getAni()->update(dt);

	texture = getAni()->texture;
}

void MultiDirAni::setDir(int nextDir)
{
	if (dir == nextDir) return;

	float currentFrame = getAni()->currentFrame;
	bool isEnd = getAni()->isEnd;
	bool isLoopEnd = getAni()->isLoopEnd;

	dir = nextDir;
	update(0);

	getAni()->currentFrame = currentFrame;
	getAni()->isEnd = isEnd;
	getAni()->isLoopEnd = isLoopEnd;
}

void MultiDirAni::setDir(float nextAngle, bool isAngle)
{
	int dirAngle = D3DXToDegree(nextAngle) + 23;

	if (dirAngle < 0)
	{
		dirAngle += 360;
	}

	setDir(dirAngle / 45);
}

void MultiDirAni::init()
{
	for (int i = 0; i < 8; i++)
	{
		ani[i]->currentFrame = 0;
		ani[i]->isEnd = false;
		ani[i]->isLoopEnd = false;
	}
}

Animation * MultiDirAni::getAni()
{
	return ani[dir];
}
