#pragma once
#include "Scene.h"
#include "Sprite.h"

class MainScene :
	public Scene
{
public:
	MainScene();
	~MainScene();

	void update(float dt);

	Sprite* bg;

	Sprite* button[3];
};

