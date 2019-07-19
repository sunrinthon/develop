#pragma once
#include "Entity.h"
class EnemyManager :
	public Entity
{
public:
	EnemyManager();
	~EnemyManager();

	void update(float dt);

	bool active;

	int monsterCount;
	float spawnDelay;
};

