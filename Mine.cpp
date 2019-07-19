#include "DXUT.h"
#include "Mine.h"
#include "GameManager.h"


Mine::Mine() : Object(MINE)
{
	sprite = new Sprite("image/object/mine.png");

	addChild(sprite);

	rect = sprite->rect;

	bar = new Sprite("image/ui/GUI/bar.png");
	frame = new Sprite("image/ui/GUI/frame.png");

	frame->pos = bar->pos = Vec2(13, 10);

	addChild(frame);
	addChild(bar);

	team = ENEMY;
	hp = hpOrigin = 100;
}


Mine::~Mine()
{
}

void Mine::decreaseHp(int damage)
{
	Unit::decreaseHp(damage);

	cout << "mine hp: " << hp << endl;

	if (hp == 0)
	{
		int goldChanceInt = (1 / gm.goldChance) - 1;
		int ironChanceInt = (1 / gm.ironChance) - 1;

		if (!random(0, goldChanceInt))
		{
			gm.ingame->addItem(ITEM_GOLD_ORE, center());
		}
		else if (!random(0, ironChanceInt))
		{
			gm.ingame->addItem(ITEM_IRON_ORE, center());
		}
		else
		{
			gm.ingame->addItem(ITEM_STONE_ORE, center());
		}

		hp = hpOrigin;
	}

	bar->visibleRect.right = ((float)hp / hpOrigin) * bar->rect.right;
}