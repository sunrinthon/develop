#include "DXUT.h"
#include "Weapon.h"
#include "World.h"
#include "GameManager.h"
#include "Asset.h"

Weapon::Weapon(WeaponType type) : type(type), state(IDLE), isAttacked(false)
{
	damage = 0;
	attackRange = 100;
	attackDelay = attackDelayOrigin = 0;

	switch (type)
	{
	case PICKAXE:
		attack = new Animation("image/weapon/pickaxe", 4, 15);
		damage = 10;
		attackRange = 100;
		attackDelay = attackDelayOrigin = 0.3;
		break;
	case WOODEN_SWORD:
		attack = new Animation("image/weapon/wooden_sword", 4, 20);
		damage = 15;
		attackRange = 100;
		attackDelay = attackDelayOrigin = 0.5;
		break;
	case STONE_KEY:
		attack = new Animation("image/weapon/stone_key", 4, 20);
		break;
	case IRON_KEY:
		attack = new Animation("image/weapon/iron_key", 4, 20);
		break;
	case GOLD_KEY:
		attack = new Animation("image/weapon/gold_key", 4, 20);
		break;
	case STONE_ORE:
		attack = new Animation("image/weapon/stone_ore", 4, 20);
		break;
	case IRON_ORE:
		attack = new Animation("image/weapon/iron_ore", 4, 20);
		break;
	case GOLD_ORE:
		attack = new Animation("image/weapon/gold_ore", 4, 20);
		break;
	case CANNON:
		attack = new Animation("image/weapon/cannon", 4, 20);
		break;
	case IRON_CANNON:
		attack = new Animation("image/weapon/iron_cannon", 4, 20);
		break;
	case GOLD_CANNON:
		attack = new Animation("image/weapon/gold_cannon", 4, 20);
		break;
	case CROSSBOW:
		attack = new Animation("image/weapon/crossbow", 4, 20);
		break;
	default:
		attack = new Animation("image/weapon/pickaxe", 4, 20);
		break;
	}
	
	addChild(attack);

	rect = attack->rect;
}

Weapon::~Weapon()
{
}

void Weapon::update(float dt)
{
	if (state == IDLE)
	{
		if (attackDelay < attackDelayOrigin)
		{
			attackDelay += dt;
		}
		else
		{
			if (world.getKeyState('G') == 2)
			{
				changeState(ATTACK);
			}
		}
	}
	else if (state == ATTACK)
	{
		attack->update(dt);
		
		if ((int)attack->currentFrame == 2 && !isAttacked)
		{
			attackUpdate();
			isAttacked = true;
		}
		if (attack->isLoopEnd)
		{
			if (type == STONE_KEY || type == IRON_KEY|| type == GOLD_KEY)
			{
				if (checkAttack(gm.ingame->box))
				{
					DXUT_PlaySound(asset.sounds[L"sound/crashbox.wav"]);
					gm.ingame->box->openBox(type);
					gm.ui->useItem();
				}
			}
			else if (type == STONE_ORE || type == IRON_ORE || type == GOLD_ORE)
			{
				if (checkAttack(gm.ingame->furnace[0]))
				{
					if (!gm.ingame->furnace[0]->isSmelting)
					{
						gm.ingame->furnace[0]->smelt(type);
						gm.ui->useItem();
					}
				}
				else if (checkAttack(gm.ingame->furnace[1]))
				{
					if (!gm.ingame->furnace[1]->isSmelting)
					{
						gm.ingame->furnace[1]->smelt(type);
						gm.ui->useItem();
					}
				}
			}
			else if (type == CANNON)
			{
				if (!gm.ingame->player->onAir)
				{
					Structure* s = gm.ingame->addStructure(STRUCTURE_CANNON, gm.ingame->player->center());
					s->scale.x = gm.ingame->player->scale.x;
					s->pos.y -= 10;
					gm.ui->useItem();
				}
			}
			else if (type == IRON_CANNON)
			{
				if (!gm.ingame->player->onAir)
				{
					Structure* s = gm.ingame->addStructure(STRUCTURE_IRON_CANNON, gm.ingame->player->center());
					s->scale.x = gm.ingame->player->scale.x;
					s->pos.y -= 10;
					gm.ui->useItem();
				}
			}
			else if (type == GOLD_CANNON)
			{
				if (!gm.ingame->player->onAir)
				{
					Structure* s = gm.ingame->addStructure(STRUCTURE_GOLD_CANNON, gm.ingame->player->center());
					s->scale.x = gm.ingame->player->scale.x;
					s->pos.y -= 10;
					gm.ui->useItem();
				}
			}
			else if (type == CROSSBOW)
			{
				if (!gm.ingame->player->onAir)
				{
					Structure* s = gm.ingame->addStructure(STRUCTURE_CROSSBOW, gm.ingame->player->center());
					s->scale.x = gm.ingame->player->scale.x;
					s->pos.y -= 10;
					gm.ui->useItem();
				}
			}
			isAttacked = false;
			attackDelay = 0;
			changeState(IDLE);
		}
	}
}

void Weapon::attackUpdate()
{
	if (type == PICKAXE)
	{
		for (auto iter : gm.ingame->objectList)
		{
			if (iter->unitType != MINE) continue;

			if (checkAttack(iter))
			{
				DXUT_PlaySound(asset.sounds[L"sound/mile.wav"]);
				gm.ingame->shake(0.03, 3, damage);
				Timer* t = gm.ingame->addTimer(0.01, 2);
				t->onTick = [=]() {
					for (int i = 0; i < 3; i++)
					{
						Vec2 addPos = iter->center() + Vec2(random(-50, 50), random(-50, 50));
						Particle* p = gm.ingame->addParticle("image/Effect/star/" + to_string(random(0, 1)) + ".png", MILLING, addPos);
						p->moveAngle = angle(gm.ingame->player->center(), addPos);
					}
				};

				iter->decreaseHp(damage);
			}
		}

		for (auto iter : gm.ingame->characterList)
		{
			if (iter->team != ENEMY) continue;

			if (checkAttack(iter))
			{
				iter->decreaseHp(damage);
			}
		}
	}
	else if (type == WOODEN_SWORD)
	{
		for (auto iter : gm.ingame->characterList)
		{
			if (iter->team != ENEMY) continue;

			if (checkAttack(iter))
			{
				DXUT_PlaySound(asset.sounds[L"sound/slash.wav"]);

				iter->decreaseHp(damage);
			}
		}
	}
}

void Weapon::changeState(State state)
{
	if (this->state == state) return;

	this->state = state;
}

bool Weapon::checkAttack(Unit * unit)
{
	if (distance(gm.ingame->player->center(), unit->center()) < attackRange)
	{
		if(type == WOODEN_SWORD)
		{
			int angleWithUnit = D3DXToDegree(angle(gm.ingame->player->center(), unit->center()));

			if (gm.ingame->player->scale.x > 0)
			{
				if (-60 < angleWithUnit && angleWithUnit < 60)
				{
					return true;
				}
			}
			else
			{
				if (-120 > angleWithUnit || angleWithUnit > 120)
				{
					return true;
				}
			}
		}
		else
		{
			return true;
		}
	}

	return false;
}
