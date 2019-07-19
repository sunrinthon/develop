#include "DXUT.h"
#include "LoadingScene.h"
#include "Asset.h"
#include "World.h"
#include "MainScene.h"


LoadingScene::LoadingScene()
{
	bg = new Sprite("image/loading/bg.png");
	addChild(bg);

	bar = new Sprite("image/loading/bar.png");
	addChild(bar);
	bar->setCenter(Vec2(628, 474.5));

	asset.ready("image/");
	asset.getSound(L"sound/background.wav");
	asset.getSound(L"sound/cannon.wav");
	asset.getSound(L"sound/crashbox.wav");
	asset.getSound(L"sound/crossbow.wav");
	asset.getSound(L"sound/hit.wav");
	asset.getSound(L"sound/main.wav");
	asset.getSound(L"sound/slash.wav");
	asset.getSound(L"sound/mile.wav");



}


LoadingScene::~LoadingScene()
{
}

void LoadingScene::update(float dt)
{
	Scene::update(dt);

	bar->visibleRect.right = ((float)asset.filesLoaded / (float)asset.filesToLoad) * bar->rect.right;

	for (int i = 0; i < 3; i++)
	{
		if (asset.filesToLoad == asset.filesLoaded)
		{
			world.changeScene(new MainScene());
			return;
		}
		asset.loadNext();
	}
}
