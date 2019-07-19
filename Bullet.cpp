#include "DXUT.h"
#include "Bullet.h"


Bullet::Bullet(BulletType type, int damage, Unit* target)
	:type(type), damage(damage), target(target)
{
	image = new Sprite("image/bullet/" + to_string(type) + ".png");
	addChild(image);
	rect = image->rect;

	speed = 700;

	rotationCenter = rect.center();
}


Bullet::~Bullet()
{
}

void Bullet::update(float dt)
{
	if (deleting) return;

	Entity::update(dt);

	if (!target || target->hp <= 0)
	{
		deleting = true;
	}

	rotation = moveAngle;
	moveAngle = angle(center(), target->center());
	pos += Vec2(cos(moveAngle), sin(moveAngle)) * speed * dt;

	if (deleting) return;

	if (distance(center(), target->center()) < 50)
	{
		if (target)
			target->decreaseHp(damage);

		deleting = true;
	}
}