#pragma once
#include "Scene.h"
#include "Sprite.h"

class ControlScene :
	public Scene
{
public:
	ControlScene();
	~ControlScene();

	void update(float dt);

	Sprite* bg;
	Sprite* closeButton;
};

