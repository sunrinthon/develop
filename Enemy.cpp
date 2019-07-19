#include "DXUT.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Character.h"
#include "Money.h"

Enemy::Enemy(EnemyType type)
	:type(type), target(nullptr)
{
	idle = new Animation("image/Character/Enemy/" + to_string(type) + "/move", 1, 1);
	move = new Animation("image/Character/Enemy/" + to_string(type) + "/move", 2, 3);

	attackDelay = attackDelayOrigin = 1;

	switch (type)
	{
	case ENEMY_NORMAL:
		attack = new Animation("image/Character/Enemy/" + to_string(type) + "/attack", 3, 10);
		speed = 60;
		damage = 10;
		hp = hpOrigin = 50;
		break;
	case ENEMY_SHIELD:
		attack = new Animation("image/Character/Enemy/" + to_string(type) + "/attack", 6, 10);
		speed = 40;
		damage = 5;
		hp = hpOrigin = 130;
		break;
	case ENEMY_MAGE:
		attack = new Animation("image/Character/Enemy/" + to_string(type) + "/attack", 5, 10);
		speed = 50;
		damage = 15;
		hp = hpOrigin = 60;
		attackDelay = attackDelayOrigin = 3;
		break;
	default:
		attack = new Animation("image/Character/Enemy/" + to_string(type) + "/attack", 5, 10);
		break;
	}

	addChild(idle);
	addChild(attack);
	addChild(move);

	rect = move->rect;
	play = move;
	scaleCenter = rect.center();

	bar = new Sprite("image/ui/GUI/hp_bar.png");
	frame = new Sprite("image/ui/GUI/hp_frame.png");

	frame->pos = bar->pos = Vec2(-13, -8);

	addChild(frame);
	addChild(bar);
	frame->scaleCenter = bar->scaleCenter = frame->rect.center();

	team = ENEMY;
	state = MOVE;
}


Enemy::~Enemy()
{
}

void Enemy::render()
{
	Character::render();

	frame->render();

	bar->render();
}

void Enemy::update(float dt)
{
	Character::update(dt);

	if (isLeft)
	{
		scale.x = -1;
		frame->scale.x = bar->scale.x = -1;
	}

	if (hp >= 0)
	{
		bar->visibleRect.right = ((float)hp / hpOrigin) * bar->rect.right;
	}

	if (state != DIE) {
		moveUpdate(dt);
		attackUpdate(dt);
	}

	dieUpdate(dt);
}

void Enemy::moveUpdate(float dt)
{
	if (state != MOVE) return;

	if (type == ENEMY_NORMAL || type == ENEMY_SHIELD)
	{
		if (!target)
		{
			for (auto c : gm.ingame->objectList)
			{
				if (team == c->team) continue;

				if (abs(c->center().x - center().x) < 50 && c->hp > 0 && abs(center().y - c->center().y) < 100)
					target = c;
			}

			if (abs(gm.ingame->player->center().x - center().x) < 50 && gm.ingame->player->hp > 0)
				target = gm.ingame->player;

			if (isLeft)
				pos.x -= speed * dt;
			else
				pos.x += speed * dt;
		}

		if (target)
		{
			if (abs(target->center().x - center().x) > 50 || target->hp <= 0)
				target = nullptr;

			changeState(ATTACK);
		}
	}

	else if (type == ENEMY_MAGE)
	{
		if (!target)
		{
			for (auto c : gm.ingame->objectList)
			{
				if (team == c->team) continue;

				if (abs(c->center().x - center().x) < 200 && c->hp > 0 )
					target = c;
			}

			if (abs(gm.ingame->player->center().x - center().x) < 200 && 
				gm.ingame->player->hp > 0 && abs(center().y - gm.ingame->player->center().y) < 100)
				target = gm.ingame->player;

			if (isLeft)
				pos.x -= speed * dt;
			else
				pos.x += speed * dt;
		}

		if (target)
		{
			if (abs(target->center().x - center().x) > 200 || target->hp <= 0)
				target = nullptr;

			changeState(ATTACK);
		}
	}

}

void Enemy::attackUpdate(float dt)
{
	if (!target)
	{
		changeState(MOVE);
	}

	if (state != ATTACK || !target) return;

	attackDelay += dt;

	if (target->hp <= 0) {
		target = nullptr;
	}

	if (type == ENEMY_NORMAL || type == ENEMY_SHIELD)
	{
		if (target)
		{
			if (attackDelay > attackDelayOrigin && (int)attack->currentFrame == 2)
			{
				target->decreaseHp(damage);
				attackDelay = 0;
			}

			if (distance(center(), target->center()) > 60 && attack->isLoopEnd)
			{
				target = nullptr;
				changeState(MOVE);
			}
		}
	}

	else if (type == ENEMY_MAGE)
	{
		if (target && attackDelay > attackDelayOrigin && (int)attack->isLoopEnd)
		{
			Bullet* b = new Bullet(BULLET_MAGE, damage, target);
			b->setCenter(center());
			gm.ingame->addChild(b);
			gm.ingame->bulletList.push_back(b);
			attackDelay = 0;
		}

		if (target)
		{
			if (distance(center(), target->center()) > 200 && attack->isLoopEnd)
			{
				target = nullptr;
				changeState(MOVE);
			}
		}
	}

}

void Enemy::dieUpdate(float dt)
{
	if (state != DIE) return;

	deleting = true;

	gm.ingame->addEffect("image/character/die", 6, 15, center());
	Particle* p = gm.ingame->addParticle(play->texture, center());
	p->scale = scale;
	p->color.a = 1;
	p->fadeSpeed = 3;
	p->fadeIn = false;

}

void Enemy::decreaseHp(int damage)
{
	Unit::decreaseHp(damage);

	if(hp <= 0)
	{
		Money* m = new Money();
		gm.ingame->addChild(m);
		m->setCenter(center());
		gm.ingame->moneyList.push_back(m);

		changeState(DIE);

		bar->visible = frame->visible = false;
	}
}
