#include "DXUT.h"
#include "Money.h"
#include "GameManager.h"

Money::Money()
	:isFade(false)
{
	image = new Sprite("image/ui/money.png");
	addChild(image);

	rect = image->rect;
}


Money::~Money()
{
}

void Money::update(float dt)
{
	Entity::update(dt);

	targetPos = Vec2(77, 123) - gm.ingame->pos;

	setCenter(center() + (targetPos - center()) * 0.05);

	if (distance(targetPos, center()) < 30)
	{
		isFade = true;
	}

	if (isFade)
	{
		image->color.a -= dt;
		if (image->color.a < 0) {
			gm.money += 10;

			deleting = true;
		}
	}

}
