#include "DXUT.h"
#include "Item.h"
#include "GameManager.h"

Item::Item(ItemType type): type(type), followTarget(nullptr), deleteTimer(0), deleteTimerOrigin(5)
{
	switch (type)
	{
	case ITEM_STONE_ORE:
		sprite = new Sprite("image/item/3.png");
		break;
	case ITEM_IRON_ORE:
		sprite = new Sprite("image/item/4.png");
		break;
	case ITEM_GOLD_ORE:
		sprite = new Sprite("image/item/5.png");
		break;
	case ITEM_STONE_KEY:
		sprite = new Sprite("image/item/6.png");
		break;
	case ITEM_IRON_KEY:
		sprite = new Sprite("image/item/7.png");
		break;
	case ITEM_GOLD_KEY:
		sprite = new Sprite("image/item/8.png");
		break;
	case ITEM_STRUCTURE_CANNON:
		sprite = new Sprite("image/item/9.png");
		break;
	case ITEM_STRUCTURE_IRON_CANNON:
		sprite = new Sprite("image/item/10.png");
		break;
	case ITEM_STRUCTURE_GOLD_CANNON:
		sprite = new Sprite("image/item/11.png");
		break;
	case ITEM_STRUCTURE_CROSSBOW:
		sprite = new Sprite("image/item/12.png");
		break;
	}
	addChild(sprite);

	rect = sprite->rect;

	onAir = true;
	gravity = 0;
	jumpSpeed = 600;
	speed = random(-300, 300);
}


Item::~Item()
{
}

void Item::update(float dt)
{
	Entity::update(dt);

	if (onAir)
	{
		pos.x += speed * dt;

		gravity += 2000 * dt;

		pos.y -= (jumpSpeed - gravity) * dt;


		for (int i = 90; i < 450; i += 2)
		{
			float tmpAngle = D3DXToRadian(i);

			Vec2 tmpPos = center() + Vec2(cos(tmpAngle), sin(tmpAngle)) * 25;

			if (i == 90)
			{
				if (onAir && gm.bitmap->getBit(tmpPos.x, tmpPos.y))
				{
					onAir = false;
					gravity = 0;
				}
			}
			else if (i == 270)
			{
				Vec2 checkPos = center() + Vec2(cos(tmpAngle), sin(tmpAngle)) * 30;

				if (gm.bitmap->getBit(checkPos.x, checkPos.y))
				{
					gravity = 100;
					jumpSpeed = 0;
				}
			}
			else if (i == 360 || i == 180)
			{
				if (gm.bitmap->getBit(tmpPos.x, tmpPos.y))
				{
					speed = 0;
				}
			}

			while (gm.bitmap->getBit(tmpPos.x, tmpPos.y))
			{
				pos -= Vec2(cos(tmpAngle), sin(tmpAngle));
				tmpPos = center() + Vec2(cos(tmpAngle), sin(tmpAngle)) * 25;
			}
		}
	}
	else
	{
		bool isInventoryFull = true;

		for (int i = 0; i < 10; i++)
		{
			if (gm.inventory[i].type == NONE)
			{
				isInventoryFull = false;
				break;
			}
			if (gm.inventory[i].type == type)
			{
				isInventoryFull = false;
				break;
			}
		}

		if (!isInventoryFull && distance(gm.ingame->player->center(), center()) < 200)
		{
			followTarget = gm.ingame->player;
		}
		else
		{
			followTarget = nullptr;
		}

		Vec2 targetPos = Vec2(0, 0);

		if (followTarget)
		{
			targetPos = followTarget->center();

			setCenter(center() + (targetPos - center()) * 0.05);

			if (distance(gm.ingame->player->center(), center()) < 30)
			{
				gm.ui->addItem(type);

				Timer* t = gm.ingame->addTimer(0.01, 6);
				t->onTick = [=]() {
					for (int i = 0; i < 5; i++)
					{
						Vec2 addPos = gm.ingame->player->center() + Vec2(random(-50, 50), random(-50, 50));
						Particle* p = gm.ingame->addParticle("image/Effect/star/" + to_string(random(0, 1)) + ".png", STAR, addPos);
						p->moveAngle = angle(gm.ingame->player->center(), addPos);
					}
				};

				deleting = true;
			}
		}
	}
}
