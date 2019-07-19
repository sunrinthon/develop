#include "DXUT.h"
#include "Structure.h"
#include "Particle.h"
#include "GameManager.h"
#include "Asset.h"

Structure::Structure(StructureType type)
	: Object(STRUCTURE), type(type), target(nullptr)
{
	attackDelay = attackDelayOrigin = 0.5f;
	hp = hpOrigin = 100;
	damage = 10;

	if (type == STRUCTURE_CANNON)
	{
		attack = new Animation("image/object/structure/cannon", 6, 30);
		idle = new Animation("image/object/structure/cannon", 1, 3);
		attackDelay = attackDelayOrigin = 1.5f;
		hp = hpOrigin = 100;
		damage = 20;
	}
	else if (type == STRUCTURE_IRON_CANNON)
	{
		attack = new Animation("image/object/structure/iron_cannon", 7, 30);
		idle = new Animation("image/object/structure/iron_cannon", 1, 3);
		attackDelay = attackDelayOrigin = 1.3f;
		hp = hpOrigin = 150;
		damage = 23;
	}
	else if (type == STRUCTURE_GOLD_CANNON)
	{
		attack = new Animation("image/object/structure/gold_cannon", 7, 30);
		idle = new Animation("image/object/structure/gold_cannon", 1, 3);
		attackDelay = attackDelayOrigin = 1.1f;
		hp = hpOrigin = 200;
		damage = 28;
	}
	else
	{
		attack = new Animation("image/object/structure/crossbow", 6, 30);
		idle = new Animation("image/object/structure/crossbow", 1, 3);
		attackDelay = attackDelayOrigin = 0.2f;
		hp = hpOrigin = 100;
		damage = 10;
	}

	addChild(attack);
	addChild(idle);
	
	rect = idle->rect;
	play = idle;

	bar = new Sprite("image/ui/GUI/hp_bar.png");
	frame = new Sprite("image/ui/GUI/hp_frame.png");

	frame->pos.x = bar->pos.x = 35;

	frame->scaleCenter = bar->scaleCenter = frame->rect.center();

	addChild(frame);
	addChild(bar);

	team = ALLY;

	attackRange = 300;

	renderChildrenEnabled = false;
	scaleCenter = rect.center();
}


Structure::~Structure()
{
}

void Structure::update(float dt)
{
	play->update(dt);

	if (hp >= 0)
	{
		bar->visibleRect.right = ((float)hp / hpOrigin) * bar->rect.right;
	}

	if (state != DIE)
	{
		idleUpdate(dt);
		attackUpdate(dt);
	}
	dieUpdate(dt);
}

void Structure::render()
{
	Object::render();

	play->render();

	frame->render();

	bar->render();
}

void Structure::attackUpdate(float dt)
{
	if (state == ATTACK)
	{
		if ((int)attack->currentFrame == 1 && target && target->hp > 0)
		{
			if (type == STRUCTURE_CROSSBOW)
			{
				Bullet* b = new Bullet(BULLET_ARROW, damage, target);
				b->setCenter(center());
				gm.ingame->addChild(b);
				gm.ingame->bulletList.push_back(b);
				DXUT_PlaySound(asset.sounds[L"sound/crossbow.wav"]);

			}
			else
			{
				Bullet* b = new Bullet(BULLET_BASIC, damage, target);
				b->setCenter(center());
				gm.ingame->addChild(b);
				gm.ingame->bulletList.push_back(b);
			}
			attack->currentFrame++;
		}

		if (target && target->state == DIE)
		{
			target = nullptr;
		}

		if (attack->isLoopEnd)
		{
			changeState(IDLE);
		}
	}

	if (state != IDLE && state != MOVE) return;

	if (target)
	{
		if (target->center().x < center().x)
		{
			if (target->center().x > 0)
			{
				scale.x = -1;
				frame->scale.x = bar->scale.x = -1;
			}
		}
		else
		{
			scale.x = 1;
			frame->scale.x = bar->scale.x = 1;
		}

		attackDelay += dt;

		if (attackDelay > attackDelayOrigin)
		{
			attackDelay = 0;
			changeState(ATTACK);
		}

		if (abs(target->center().x - center().x) > attackRange && attack->isLoopEnd)
		{
			target = nullptr;
		}
	}
}

void Structure::dieUpdate(float dt)
{
	if (state != DIE) return;

	Particle* p = gm.ingame->addParticle(play->texture, center());
	p->scale = scale;
	p->color.a = 1;
	p->fadeSpeed = 3;
	p->fadeIn = false;

	deleting = true;
}

void Structure::idleUpdate(float dt)
{
	if (state != IDLE) return;

	for (auto c : gm.ingame->characterList)
	{
		if (team == c->team || target) continue;

		if (abs(c->center().x - center().x) < attackRange && c->hp > 0) {
			target = c;
		}
	}
}

void Structure::changeState(State state)
{
	if (this->state == state) return;

	this->state = state;

	switch (state)
	{
	case IDLE:
		play = idle;
		break;
	case ATTACK:
		play = attack;
		break;
	case DIE:
		play = idle;
		break;
	default:
		break;
	}

	play->currentFrame = 0;
	play->update(0);
}

void Structure::decreaseHp(int damage)
{
	Unit::decreaseHp(damage);

	if (hp <= 0)
	{
		changeState(DIE);
		frame->visible = bar->visible = false;
	}

}

