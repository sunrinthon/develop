#include "DXUT.h"
#include "EnemyManager.h"
#include "GameManager.h"

EnemyManager::EnemyManager()
	:active(false), monsterCount(0), spawnDelay(0)
{
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::update(float dt)
{
	Entity::update(dt);

	if (!active) return;

	if (monsterCount == 0)
	{
		gm.ingame->isDelay = true;
		gm.ingame->delayTimer = 0;
		active = false;
	}

	spawnDelay += dt;

	if (gm.round == 1)
	{
		if (spawnDelay >= 3.f)
		{
			if (monsterCount > 2)
				gm.ingame->addEnemy(ENEMY_NORMAL);
			else
				gm.ingame->addEnemy(ENEMY_MAGE);

			spawnDelay = 0;

			monsterCount--;
		}
	}

	if (gm.round == 2)
	{
		if (spawnDelay >= 3.f)
		{
			if (monsterCount > 2)
				gm.ingame->addEnemy(ENEMY_NORMAL);
			else
				gm.ingame->addEnemy(ENEMY_MAGE);

			spawnDelay = 0;

			monsterCount--;
		}
	}

	if (gm.round == 3)
	{
		if (spawnDelay >= 3.f)
		{
			if (monsterCount <= 16 && monsterCount >= 9)
				gm.ingame->addEnemy(ENEMY_NORMAL);
			if (monsterCount <= 8 && monsterCount >= 3)
				gm.ingame->addEnemy(ENEMY_SHIELD);
			else
				gm.ingame->addEnemy(ENEMY_MAGE);

			spawnDelay = 0;

			monsterCount--;
		}
	}

	if (gm.round == 4)
	{
		if (spawnDelay >= 3.f)
		{
			if (monsterCount <= 20 && monsterCount >= 14)
				gm.ingame->addEnemy(ENEMY_NORMAL);
			if (monsterCount <= 13 && monsterCount >= 4)
				gm.ingame->addEnemy(ENEMY_SHIELD);
			else
				gm.ingame->addEnemy(ENEMY_MAGE);

			spawnDelay = 0;

			monsterCount--;
		}
	}

	if (gm.round == 5)
	{
		if (spawnDelay >= 3.f)
		{
			if (monsterCount <= 16 && monsterCount >= 9)
				gm.ingame->addEnemy(ENEMY_SHIELD);
			else
				gm.ingame->addEnemy(ENEMY_MAGE);

			spawnDelay = 0;

			monsterCount--;
		}
	}

	if (gm.round == 6)
	{
		if (spawnDelay >= 3.f)
		{
			if (monsterCount <= 24 && monsterCount >= 18)
				gm.ingame->addEnemy(ENEMY_NORMAL);
			if (monsterCount <= 18 && monsterCount >= 7)
				gm.ingame->addEnemy(ENEMY_SHIELD);
			else
				gm.ingame->addEnemy(ENEMY_MAGE);

			spawnDelay = 0;

			monsterCount--;
		}
	}


	if (gm.round == 7)
	{
		if (spawnDelay >= 3.f)
		{
			if (monsterCount <= 26 && monsterCount >= 16)
				gm.ingame->addEnemy(ENEMY_NORMAL);
			if (monsterCount <= 16 && monsterCount >= 4)
				gm.ingame->addEnemy(ENEMY_SHIELD);
			else
				gm.ingame->addEnemy(ENEMY_MAGE);

			spawnDelay = 0;

			monsterCount--;
		}
	}

	if (gm.round == 8)
	{
		if (spawnDelay >= 3.f)
		{
			if (monsterCount <= 26 && monsterCount >= 9)
				gm.ingame->addEnemy(ENEMY_SHIELD);
			else
				gm.ingame->addEnemy(ENEMY_MAGE);

			spawnDelay = 0;

			monsterCount--;
		}
	}

	if (gm.round == 9)
	{
		if (spawnDelay >= 3.f)
		{
			if (monsterCount <= 30 && monsterCount >= 26)
				gm.ingame->addEnemy(ENEMY_SHIELD);
			else
				gm.ingame->addEnemy(ENEMY_MAGE);

			spawnDelay = 0;

			monsterCount--;
		}
	}

	if (gm.round == 10)
	{
		if (spawnDelay >= 3.f)
		{
			if (monsterCount <= 40 && monsterCount >= 36)
				gm.ingame->addEnemy(ENEMY_SHIELD);
			else
				gm.ingame->addEnemy(ENEMY_MAGE);

			spawnDelay = 0;

			monsterCount--;
		}
	}

}