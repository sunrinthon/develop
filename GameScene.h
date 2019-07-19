#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "UI.h"
#include "Bitmap.h"
#include "Unit.h"
#include "Character.h"
#include "Object.h"
#include "Particle.h"
#include "Player.h"
#include "Item.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Structure.h"
#include "Box.h"
#include "Mine.h"
#include "Furnace.h"
#include "EnemyManager.h"
#include "Money.h"

class GameScene
	:public Scene
{
public:
	GameScene();
	~GameScene();

	void render();
	void update(float dt);

	void addEnemy(EnemyType type);


	Particle* addParticle(Texture* texture, Vec2 addPos);
	Particle* addParticle(string path, ParticleType type, Vec2 addPos = Vec2(0, 0));

	Mine* addMine(Vec2 addPos);
	Furnace* addFurnace(Vec2 addPos);
	Structure* addStructure(StructureType type, Vec2 addPos);
	Item* addItem(ItemType type, Vec2 addPos);
	Timer* addTimer(float duration, int count);
	Animation* addEffect(string path, int frameNum, float fps, Vec2 addPos);

	UI* ui;
	Player* player;
	Sprite* bg;
	Mine* mine;
	Box* box;
	Furnace* furnace[2];
	EnemyManager* enemyManager;
	Sprite* clear;
	Sprite* over;
	Sprite* respawn;

	list<Character*> characterList;
	list<Object*> objectList;
	list<Item*> itemList;
	list<Bullet*> bulletList;
	list<Particle*> particleList;
	list<Animation*> effectList;
	list<Money*> moneyList;

	bool gameOver;
	bool gameClear;
	bool isDelay;
	bool isFadeOut;

	float delayTimer;
};