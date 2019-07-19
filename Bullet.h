#pragma once
#include "Entity.h"
#include "Unit.h"
#include "Sprite.h"

class Bullet :
	public Entity
{
public:
	Bullet(BulletType type, int damage, Unit* target);
	~Bullet();

	void update(float dt);

	BulletType type;
	Sprite* image;
	Unit* target;

	float moveAngle;
	float damage;
	float speed;

};
