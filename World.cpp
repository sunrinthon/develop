#include "DXUT.h"
#include "World.h"
#include "Asset.h"
#include "GameScene.h"
#include "MainScene.h"
#include "LoadingScene.h"

World::World() :currentScene(nullptr), isFast(false)
{
}

World::~World()
{
}

void World::init()
{
	asset.init();
	cout.precision(3);
	D3DXCreateSprite(DXUTGetD3D9Device(), &rootSprite);
	changeScene(new LoadingScene());
	ZeroMemory(lastKeys, sizeof(lastKeys));
	ZeroMemory(currentKeys, sizeof(currentKeys));
}

void World::render()
{
	if (currentScene) currentScene->render();
}

void World::update(float dt)
{
	if (getKeyState(VK_F11) == 1)
	{
		isFast = !isFast;
	}
	if (isFast)
	{
		dt = dt * 2;
	}

	if(currentScene) currentScene->update(dt);


	for(int i=0; i<256; i++)
	{
		lastKeys[i] = currentKeys[i];
		currentKeys[i] = GetAsyncKeyState(i) & 0x8000;
	}

	GetCursorPos(&mousePoint);
	ScreenToClient(DXUTGetHWND(), &mousePoint);

	for(auto timer : timerList)
	{
		timer->update(dt);
	}

	timerList.erase(remove_if(timerList.begin(), timerList.end(),
		[&](Timer* iter) {
			bool removing = iter->removing;
			if (removing) {
				SAFE_DELETE(iter);
			}
			return removing;
		}), timerList.end());
}

void World::dispose()
{
	for (auto timer : timerList)
	{
		SAFE_DELETE(timer);
	}
	asset.dispose();
	SAFE_DELETE(currentScene);
	SAFE_RELEASE(rootSprite);
}

void World::changeScene(Scene* scene)
{
	if(currentScene) SAFE_DELETE(currentScene);
	currentScene = scene;
}

int World::getKeyState(int vk)
{
	if(currentKeys[vk] && lastKeys[vk]) return 2;
	if(currentKeys[vk] && !lastKeys[vk]) return 1;
	if(!currentKeys[vk] && lastKeys[vk]) return -1;
	return -2;
}

Vec2 World::getMousePos()
{
	return Vec2(mousePoint.x, mousePoint.y);
}

World world;