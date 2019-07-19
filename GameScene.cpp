#include "DXUT.h"
#include "GameScene.h"
#include "World.h"
#include "GameManager.h"
#include "Asset.h"
#include "MainScene.h"

GameScene::GameScene()
	:gameOver(false), isDelay(true), delayTimer(0), gameClear(false), isFadeOut(false)
{
	gm.ingame = this;

	ui = new UI();
	
	Bitmap* bitmap = new Bitmap();
	addChild(bitmap);

	bg = new Sprite("image/bg.png");
	addChild(bg);
	
	box = new Box();
	addChild(box);
	box->setCenter(Vec2(885, 1325));
	objectList.push_back(box);

	player = new Player();
	addChild(player);
	player->setCenter(Vec2(883, 1100));
	characterList.push_back(player);
	gm.ui->focusInventory(0);

	follow(player);

	mine = addMine(Vec2(883, 1200));
	furnace[0] = addFurnace(Vec2(740, 1030));
	furnace[1] = addFurnace(Vec2(1030, 1030));
	//asset.getSound(L"sound/test.wav");

	//DXUT_PlaySoundLooping(asset.sounds[L"sound/test.wav"]);

	enemyManager = new EnemyManager();
	addChild(enemyManager);

	clear = new Sprite("image/ui/clear.png");
	clear->color.a = 0;

	over = new Sprite("image/ui/over.png");
	over->color.a = 0;

	respawn = new Sprite("image/ui/respawn.png");
	respawn->color.a = 0;

	DXUT_PlaySoundLooping(asset.sounds[L"sound/background.wav"]);

}

GameScene::~GameScene()
{
	SAFE_DELETE(ui);
	SAFE_DELETE(clear);
	SAFE_DELETE(over);
	SAFE_DELETE(respawn);
}

void GameScene::render()
{
	Scene::render();

	for (auto iter : objectList)
	{
		iter->render();
	}

	for (auto iter : characterList)
	{
		iter->render();
	}

	for (auto iter : itemList)
	{
		iter->render();
	}

	for (auto iter : bulletList)
	{
		iter->render();
	}

	for (auto iter : particleList)
	{
		iter->render();
	}

	for (auto iter : effectList)
	{
		iter->render();
	}

	for (auto iter : moneyList)
	{
		iter->render();
	}

	ui->render();

	clear->render();
	over->render();
	respawn->render();
}

void GameScene::update(float dt)
{

	if (world.getKeyState(VK_F4) == 1)
	{
		gameClear = true;
	}
	if(world.getKeyState(VK_F5) == 1)
	{
		gameOver = true;
	}

	if (gameClear)
	{
		clear->color.a += 2 * dt;

		if (clear->color.a >= 5)
		{
			world.changeScene(new MainScene());
			return;
		}

		return;
	}
	else if (gameOver)
	{
		over->color.a += 2 * dt;

		if (over->color.a >= 5)
		{
			world.changeScene(new MainScene());
			return;
		}

		return;
	}

	if (player->isDead)
	{
		if (respawn->color.a < 1)
		{
			respawn->color.a += 3 * dt;
		}
	}
	else
	{
		if (respawn->color.a > 0)
		{
			respawn->color.a -= 3 * dt;
		}
	}

	Scene::update(dt);

	if (isDelay)
	{
		if (gm.round == 10)
			gameClear = true;

		delayTimer += dt;
		if (delayTimer > 30)
		{
			delayTimer = 0;
			isDelay = false;

			if (gm.round <= 9)
				gm.round++;

			if (gm.round == 1)
				enemyManager->monsterCount = 10;

			if (gm.round == 2)
				enemyManager->monsterCount = 14;

			if (gm.round == 3)
				enemyManager->monsterCount = 16;

			if (gm.round == 4)
				enemyManager->monsterCount = 20;

			if (gm.round == 5)
				enemyManager->monsterCount = 16;

			if (gm.round == 6)
				enemyManager->monsterCount = 24;

			if (gm.round == 7)
				enemyManager->monsterCount = 26;

			if (gm.round == 8)
				enemyManager->monsterCount = 26;

			if (gm.round == 9)
				enemyManager->monsterCount = 30;

			if (gm.round == 10)
				enemyManager->monsterCount = 40;

			enemyManager->active = true;
		}
	}

	if (world.getKeyState(VK_F3) == 1)
	{
		delayTimer = 55;
	}

	if (world.getKeyState(VK_SPACE) == 1)
	{
		Enemy* e = new Enemy(ENEMY_NORMAL);

		addChild(e);
		characterList.push_back(e);

		if (random(0, 1))
		{
			e->pos = Vec2(100, 600);
			e->isLeft = false;
		}
		else {
			e->pos = Vec2(1100, 600);
			e->isLeft = true;
		}
	}

	if (world.getKeyState(VK_F1) == 1)
	{
		addStructure(STRUCTURE_CANNON, player->center());
	}
	if (world.getKeyState(VK_F2) == 1)
	{
		addMine(player->pos);
	}

	ui->update(dt);

	objectList.erase(remove_if(objectList.begin(), objectList.end(),
		[&](Object* iter) {
			if (iter->deleting)
				removeChild(iter);
			return iter->deleting;
		}), objectList.end());

	characterList.erase(remove_if(characterList.begin(), characterList.end(),
		[&](Character* iter) {
			if (iter->deleting)
				removeChild(iter);
			return iter->deleting;
		}), characterList.end());

	particleList.erase(remove_if(particleList.begin(), particleList.end(),
		[&](Particle* iter) {
			if (iter->deleting)
				removeChild(iter);
			return iter->deleting;
		}), particleList.end());

	bulletList.erase(remove_if(bulletList.begin(), bulletList.end(),
		[&](Bullet* iter) {
			if (iter->deleting)
				removeChild(iter);
			return iter->deleting;
		}), bulletList.end());

	itemList.erase(remove_if(itemList.begin(), itemList.end(),
		[&](Item* iter) {
			if (iter->deleting)
				removeChild(iter);
			return iter->deleting;
		}), itemList.end());

	effectList.erase(remove_if(effectList.begin(), effectList.end(),
		[&](Animation* iter) {
			if (iter->isEnd)
				removeChild(iter);
			return iter->isEnd;
		}), effectList.end());

	moneyList.erase(remove_if(moneyList.begin(), moneyList.end(),
		[&](Money* iter) {
			if (iter->deleting)
				removeChild(iter);
			return iter->deleting;
		}), moneyList.end());
}

Particle * GameScene::addParticle(Texture* texture, Vec2 addPos)
{
	Particle* iter = new Particle(texture, FADE);
	addChild(iter);
	particleList.push_back(iter);
	iter->setCenter(addPos);
	return iter;
}

Particle * GameScene::addParticle(string path, ParticleType type, Vec2 addPos)
{
	Particle* iter = new Particle(path, type);
	addChild(iter);

	particleList.push_back(iter);

	iter->setCenter(addPos);
	return iter;
}

Mine * GameScene::addMine(Vec2 addPos)
{
	Mine* iter = new Mine();
	addChild(iter);
	objectList.push_back(iter);
	iter->setCenter(addPos);
	return iter;
}

Furnace * GameScene::addFurnace(Vec2 addPos)
{
	Furnace* iter = new Furnace();
	addChild(iter);
	objectList.push_back(iter);
	iter->setCenter(addPos);
	return iter;
}

Structure * GameScene::addStructure(StructureType type, Vec2 addPos)
{
	Structure* iter = new Structure(type);
	addChild(iter);
	objectList.push_back(iter);
	iter->setCenter(addPos);
	return iter;
}

Item * GameScene::addItem(ItemType type, Vec2 addPos)
{
	Item* iter = new Item(type);
	addChild(iter);
	itemList.push_back(iter);
	iter->setCenter(addPos);
	return iter;
}

Timer * GameScene::addTimer(float duration, int count)
{
	Timer* iter = new Timer();
	iter->reset(duration, count);
	iter->onFinish = [=]() {
		iter->removing = true;
	};

	return iter;
}

Animation * GameScene::addEffect(string path, int frameNum, float fps, Vec2 addPos)
{
	Animation* iter = new Animation(path, frameNum, fps, false);
	addChild(iter);
	effectList.push_back(iter);
	iter->setCenter(addPos);
	return iter;
}

void GameScene::addEnemy(EnemyType type)
{
	Enemy* e = new Enemy(type);
	addChild(e);
	characterList.push_back(e);

	Enemy* e2 = new Enemy(type);
	addChild(e2);
	characterList.push_back(e2);

	e->pos = Vec2(12, 1315);
	e->isLeft = false;

	e2->pos = Vec2(1730, 1315);
	e2->isLeft = true;
}
