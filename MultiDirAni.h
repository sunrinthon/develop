#pragma once
#include "Sprite.h"
#include "Animation.h"

class MultiDirAni :
	public Sprite
{
public:
	MultiDirAni(string path, int frameNum, float fps, bool loop = true);
	~MultiDirAni();

	void update(float dt);
	void setDir(int nextDir);
	void setDir(float nextAngle, bool isAngle);
	void init();
	Animation* getAni();

	Animation* ani[8];
	int dir;
};

