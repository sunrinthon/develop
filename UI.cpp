#include "DXUT.h"
#include "UI.h"
#include "GameManager.h"
#include "World.h"


UI::UI():focusIndex(0), trashTimer(0), particleTimer(0), particleTimerOrigin(0.7f)
{
	gm.ui = this;

	frame = new Sprite("image/ui/frame.png");
	addChild(frame);

	for (int i = 0; i < 10; i++)
	{
		inventory[i] = new Sprite("image/ui/item_icon/0.png");
		addChild(inventory[i]);
		inventory[i]->setCenter(Vec2(60 + i * 82, 57));

		inventoryCount[i] = new Text("x " + to_string(gm.inventory[i].count), 20, D3DXCOLOR(0, 0, 0, 1));
		addChild(inventoryCount[i]);
		inventoryCount[i]->setCenter(Vec2(62 + i * 82, 70));
	}

	round = new Text("ROUND 1/10", 70, D3DXCOLOR(1, 1, 1, 1));
	addChild(round);
	round->pos = Vec2(900, 20);

	money = new Text("0", 40, D3DXCOLOR(1, 1, 1, 1));
	addChild(money);
	money->setCenter(Vec2(77, 123));

	moneyIcon = new Sprite("image/ui/money.png");
	addChild(moneyIcon);
	moneyIcon->setCenter(Vec2(40, 140));

	focus = new Sprite("image/ui/focus.png");
	addChild(focus);
	focus->setCenter(Vec2(60, 57));
}


UI::~UI()
{
}

void UI::update(float dt)
{
	Entity::update(dt);

	if (gm.round != 0)
	{
		round->setText("ROUND " + to_string(gm.round) + "/10");
	}

	money->setText(to_string(gm.money));

	for (int i = 0; i < 10; i++)
	{
		inventory[i]->setPath("image/ui/item_icon/" + to_string(gm.inventory[i].type) + ".png");
	}
	for (int i = 0; i < 10; i++)
	{
		inventoryCount[i]->visible = (gm.inventory[i].type != NONE);
		inventoryCount[i]->setText("x " + to_string(gm.inventory[i].count));
	}

	for (int i = 0; i < 10; i++)
	{
		if (world.getKeyState('1' + i) == 1)
		{
			if (gm.inventory[i].type != NONE && gm.ingame->player->weapon->state != ATTACK)
			{
				focusIndex = i;
				focusInventory(i);
			}
		}
	}

	if (world.getKeyState('T') == 2)
	{
		if (focusIndex != 0)
		{
			trashTimer += dt;
			particleTimer += dt;

			if (particleTimer > particleTimerOrigin - trashTimer/2)
			{
				Particle* p = new Particle("image/effect/fire.png", FIRE);
				Vec2 spawnPos = Vec2(60 + focusIndex * 82, 57) + Vec2(random(-30, 30), random(-30, 30));
				p->setCenter(spawnPos);
				addChild(p);
				particleList.push_back(p);
				particleTimer = 0;
			}
			if (trashTimer > 2)
			{
				gm.inventory[focusIndex].count = 0;

				gm.inventory[focusIndex].type = NONE;
				focusInventory(0);
			}
		}
	}
	else if (world.getKeyState('T') == -1)
	{
		trashTimer = 0;
	}

	particleList.erase(remove_if(particleList.begin(), particleList.end(),
		[&](Particle* iter) {
			if (iter->deleting)
				removeChild(iter);
			return iter->deleting;
		}), particleList.end());
}

bool UI::checkWeapon(ItemType itemType)
{
	return true;
}

void UI::weaponChange(ItemType itemType)
{
	switch (itemType)
	{
	case ITEM_PICKAXE:
		gm.ingame->player->changeWeapon(PICKAXE);
		break;
	case ITEM_WOODEN_SWORD:
		gm.ingame->player->changeWeapon(WOODEN_SWORD);
		break;
	case ITEM_STONE_ORE:
		gm.ingame->player->changeWeapon(STONE_ORE);
		break;
	case ITEM_IRON_ORE:
		gm.ingame->player->changeWeapon(IRON_ORE);
		break;
	case ITEM_GOLD_ORE:
		gm.ingame->player->changeWeapon(GOLD_ORE);
		break;
	case ITEM_STONE_KEY:
		gm.ingame->player->changeWeapon(STONE_KEY);
		break;
	case ITEM_IRON_KEY:
		gm.ingame->player->changeWeapon(IRON_KEY);
		break;
	case ITEM_GOLD_KEY:
		gm.ingame->player->changeWeapon(GOLD_KEY);
		break;
	case ITEM_STRUCTURE_CANNON:
		gm.ingame->player->changeWeapon(CANNON);
		break;
	case ITEM_STRUCTURE_IRON_CANNON:
		gm.ingame->player->changeWeapon(IRON_CANNON);
		break;
	case ITEM_STRUCTURE_GOLD_CANNON:
		gm.ingame->player->changeWeapon(GOLD_CANNON);
		break;
	case ITEM_STRUCTURE_CROSSBOW:
		gm.ingame->player->changeWeapon(CROSSBOW);
		break;
	}
}

void UI::focusInventory(int i)
{
	if (checkWeapon(gm.inventory[i].type))
	{
		weaponChange(gm.inventory[i].type);
		focusIndex = i;
		focus->setCenter(Vec2(60 + i * 82, 57));
	}
}

void UI::useItem()
{
	if (checkWeapon(gm.inventory[focusIndex].type))
	{
		gm.inventory[focusIndex].count--;

		if (gm.inventory[focusIndex].count <= 0)
		{
			gm.inventory[focusIndex].type = NONE;
			focusInventory(0);
		}
	}
}

void UI::addItem(ItemType itemType)
{
	for (int i = 0; i < 10; i++)
	{
		if (gm.inventory[i].type == itemType)
		{
			gm.inventory[i].count++;

			return;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (gm.inventory[i].type == NONE)
		{
			gm.inventory[i].type = itemType;
			gm.inventory[i].count = 1;

			return;
		}
	}

}