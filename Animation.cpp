#include "DXUT.h"
#include "Animation.h"
#include "Asset.h"

Animation::Animation(const string& path, int frameNum, float fps, bool loop, bool png)
	:loop(loop), currentFrame(0), fps(fps), isEnd(false), isLoopEnd(false)
{
	for(int i=0; i<frameNum; i++)
	{
		Texture* t = asset.getTexture(path+"/"+to_string(i) + (png?  ".png" : ".dds"));
		textures.push_back(t);
	}
	texture = textures[0];

	visibleRect = rect = Rect(0, 0, texture->info.Width, texture->info.Height);
}

Animation::~Animation()
{
}

void Animation::update(float dt)
{
	Sprite::update(dt);

	currentFrame += dt * fps;

	if (isLoopEnd) isLoopEnd = false;
	
	if((int)currentFrame >= textures.size())
	{
		if (loop)
		{
			isLoopEnd = true;
			currentFrame = 0;
		}
		else
		{
			isEnd = true;
			currentFrame = textures.size() - 1;
		}
	}

	texture = textures[int(currentFrame)];
}