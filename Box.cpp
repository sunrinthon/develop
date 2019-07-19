#include "DXUT.h"
#include "Box.h"
#include "GameManager.h"
#include "Item.h"

Box::Box() : Object(STRUCTURE), isOpend(false), isDropped(false)
{
	idle = new Animation("image/object/box/idle", 1, 1);
	open = new Animation("image/object/box/open", 9, 18);

	addChild(idle);
	addChild(open);

	play = idle;
	rect = idle->rect;

	bar = new Sprite("image/ui/GUI/hp_bar.png");
	frame = new Sprite("image/ui/GUI/hp_frame.png");

	frame->pos = bar->pos = Vec2(-12, 5);

	addChild(frame);
	addChild(bar);

	hp = hpOrigin = 1000;
	team = ALLY;
	addItem = NONE;

	renderChildrenEnabled = false;
}


Box::~Box()
{
}

void Box::render()
{
	Object::render();

	play->render();

	frame->render();
	bar->render();
}

void Box::update(float dt)
{
	if (hp >= 0)
	{
		bar->visibleRect.right = ((float)hp / hpOrigin) * bar->rect.right;
	}

	if (isOpend)
	{
		play->update(dt);

		if ((int)play->currentFrame == 4 && !isDropped)
		{
			gm.ingame->addItem(addItem, center());
			isDropped = true;
		}

		if (play->isLoopEnd)
		{
			play = idle;
			isOpend = false;
			isDropped = false;
		}
	}

	dieUpdate(dt);
}

void Box::dieUpdate(float dt)
{
	if (hp <= 0) state = DIE;

	if (state != DIE) return;

	gm.ingame->gameOver = true;
}

void Box::openBox(WeaponType weaponType)
{
	if (weaponType == STONE_KEY)
	{
		float randomFloat = random(0.f, 1.f);

		cout << randomFloat << endl;
		if (0 <= randomFloat && randomFloat <= 0.03)
		{
			addItem = ITEM_STRUCTURE_CROSSBOW;
		}
		else if(0.03 <= randomFloat && randomFloat <= 0.06)
		{
			addItem = ITEM_STRUCTURE_GOLD_CANNON;
		}
		else if (0.06 <= randomFloat && randomFloat <= 0.2)
		{
			addItem = ITEM_STRUCTURE_IRON_CANNON;
		}
		else
		{
			addItem = ITEM_STRUCTURE_CANNON;
		}
	}
	else if (weaponType == IRON_KEY)
	{
		float randomFloat = random(0.f, 1.f);

		if (0 <= randomFloat && randomFloat <= 0.06)
		{
			addItem = ITEM_STRUCTURE_CROSSBOW;
		}
		else if (0.06 <= randomFloat && randomFloat <= 0.12)
		{
			addItem = ITEM_STRUCTURE_GOLD_CANNON;
		}
		else if (0.12 <= randomFloat && randomFloat <= 0.6)
		{
			addItem = ITEM_STRUCTURE_IRON_CANNON;
		}
		else
		{
			addItem = ITEM_STRUCTURE_CANNON;
		}
	}
	else if (weaponType == GOLD_KEY)
	{
		float randomFloat = random(0.f, 1.f);

		if (0 <= randomFloat && randomFloat <= 0.15)
		{
			addItem = ITEM_STRUCTURE_CROSSBOW;
		}
		else if (0.15 <= randomFloat && randomFloat <= 0.3)
		{
			addItem = ITEM_STRUCTURE_GOLD_CANNON;
		}
		else if (0.3 <= randomFloat && randomFloat <= 0.8)
		{
			addItem = ITEM_STRUCTURE_IRON_CANNON;
		}
		else
		{
			addItem = ITEM_STRUCTURE_CANNON;
		}
	}

	play = open;

	isOpend = true;
}
