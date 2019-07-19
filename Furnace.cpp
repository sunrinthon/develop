#include "DXUT.h"
#include "Furnace.h"
#include "GameManager.h"


Furnace::Furnace(): Object(FURNACE), isSmelting(false), smeltTimer(0), smeltTimerOrigin(7)
{
	idle = new Animation("image/object/furnace", 2, 5);
	addChild(idle);

	rect = idle->rect;


	bar = new Sprite("image/ui/GUI/bar.png");
	frame = new Sprite("image/ui/GUI/frame.png");

	frame->pos.y = bar->pos.y = -15;

	addChild(frame);
	addChild(bar);
}

Furnace::~Furnace()
{
}

void Furnace::update(float dt)
{
	Object::update(dt);

	bar->visibleRect.right = ((float)smeltTimer / smeltTimerOrigin) * bar->rect.right;

	if (isSmelting)
	{
		smeltTimer += dt;

		if (smeltTimer > smeltTimerOrigin)
		{
			if (smeltItem == STONE_ORE)
			{
				gm.ingame->addItem(ITEM_STONE_KEY, center());
			}
			else if (smeltItem == IRON_ORE)
			{
				gm.ingame->addItem(ITEM_IRON_KEY, center());
			}
			else if (smeltItem == GOLD_ORE)
			{
				gm.ingame->addItem(ITEM_GOLD_KEY, center());
			}

			smeltTimer = 0;

			isSmelting = false;
		}
	}
}

void Furnace::smelt(WeaponType smeltItem)
{
	this->smeltItem = smeltItem;

	isSmelting = true;

	Vec2 furnaceCenter = center();
	Timer* t = gm.ingame->addTimer(0.05, 6);
	t->onTick = [=]() {
		for (int i = 0; i < 5; i++)
		{
			Vec2 spawnPos = furnaceCenter + Vec2(random(-40, 40), random(-40, 40));
			gm.ingame->addParticle("image/effect/fire.png", FIRE, spawnPos);
		}
	};
}
