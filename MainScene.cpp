#include "DXUT.h"
#include "MainScene.h"
#include "World.h"
#include "GameScene.h"
#include "ControlScene.h"
#include "Asset.h"

MainScene::MainScene()
{
	bg = new Sprite("image/main/bg.png");
	addChild(bg);

	for (int i = 0; i < 3; i++)
	{
		button[i] = new Sprite("image/main/" + to_string(i) + "/0.png");
		addChild(button[i]);

		button[i]->setCenter(Vec2(640, 360 + i * 120));
	}

	DXUT_PlaySoundLooping(asset.sounds[L"sound/main.wav"]);

}


MainScene::~MainScene()
{
}

void MainScene::update(float dt)
{
	Scene::update(dt);


	for (int i = 0; i < 3; i++)
	{
		if (button[i]->rectWithPos().contain(world.getMousePos()))
		{
			button[i]->setPath("image/main/" + to_string(i) + "/1.png");

			if (world.getKeyState(VK_LBUTTON) == 1)
			{
				if (i == 0)
				{
					world.changeScene(new GameScene());
				}
				else if (i == 1)
				{
					world.changeScene(new ControlScene());
				}
				else if (i == 2)
				{
					exit(0);
				}
				return;
			}
		}
		else
		{
			button[i]->setPath("image/main/" + to_string(i) + "/0.png");
		}
	}
}
