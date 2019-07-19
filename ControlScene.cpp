#include "DXUT.h"
#include "ControlScene.h"
#include "World.h"
#include "MainScene.h"

ControlScene::ControlScene()
{
	bg = new Sprite("image/control/bg.png");
	addChild(bg);
	
	closeButton = new Sprite("image/control/close.png");
	addChild(closeButton);
	closeButton->scaleCenter = closeButton->rect.center();
	closeButton->setCenter(Vec2(1100, 100));
}


ControlScene::~ControlScene()
{
}

void ControlScene::update(float dt)
{
	Scene::update(dt);

	if (closeButton->rectWithPos().contain(world.getMousePos()))
	{
		closeButton->scale = Vec2(1.1, 1.1);

		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			world.changeScene(new MainScene());
			return;
		}
	}
	else
	{
		closeButton->scale = Vec2(1, 1);
	}
}