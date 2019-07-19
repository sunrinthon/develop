    #include "DXUT.h"
#include "Player.h"
#include "World.h"
#include "Bitmap.h"
#include "GameManager.h"
#include "Asset.h"

Player::Player() : weapon(nullptr), onAir(false), isJump(false), isDead(false), particleTimer(0), rebornTimer(0)
{
	idle = new Animation("image/Character/Player/idle", 1, 1);
	attack = new Animation("image/Character/Player/attack", 3, 3);
	move = new Animation("image/Character/Player/move", 4, 12);

	addChild(idle);
	addChild(attack);
	addChild(move);

	play = idle;
	rect = idle->rect;
	scaleCenter = rect.center();

	bar = new Sprite("image/ui/GUI/hp_bar.png");
	frame = new Sprite("image/ui/GUI/hp_frame.png");

	frame->pos = bar->pos = Vec2(-23, -20);
	
	addChild(frame);
	addChild(bar);

	frame->scaleCenter = bar->scaleCenter = frame->rect.center();

	team = ALLY;
	hp = hpOrigin = 300;
	speed = 300;
	jumpSpeed = 0;
	gravity = 0;

}

Player::~Player()
{
}

void Player::render() 
{
	if (isDead) return;
	Character::render();

	weapon->render();
	
	frame->render();
	bar->render();
}

void Player::update(float dt)
{
	Character::update(dt);

	if (isDead)
		rebornTimer += dt;

	if (rebornTimer >= 5.0f)
	{
		hp = hpOrigin;
		setCenter(Vec2(883, 1100));
		changeState(MOVE);

		rebornTimer = 0;
		isDead = false;

		bar->visible = frame->visible = true;
	}

	if (pos.x <= 12)
		pos.x = 12;

	if (pos.x >= 1730)
		pos.x = 1730;

	if (hp >= 0)
	{
		bar->visibleRect.right = ((float)hp / hpOrigin) * bar->rect.right;
	}

	weapon->update(dt);

	jumpUpdate(dt);

	colUpdate(dt);
}

void Player::colUpdate(float dt)
{
	if (onAir)
	{
		gravity += 2000 * dt;

		pos.y -= (jumpSpeed - gravity) * dt;

	}

	for (int i = 90; i < 450; i += 2)
	{
		float tmpAngle = D3DXToRadian(i);

		Vec2 tmpPos = center() + Vec2(cos(tmpAngle), sin(tmpAngle)) * 20;

		if (i == 90)
		{
			if (onAir)
			{
				if (gm.bitmap->getBit(tmpPos.x, tmpPos.y))
				{
					onAir = false;
					gravity = 0;
				}

			}
			else
			{
				Vec2 checkPos = center() + Vec2(cos(tmpAngle), sin(tmpAngle)) * 25;

				if (!gm.bitmap->getBit(checkPos.x, checkPos.y))
				{
					onAir = true;
					gravity = 0;
					jumpSpeed = 0;
				}
				else
				{
					onAir = false;
				}
			}
		}
		else if (i == 270)
		{
			Vec2 checkPos = center() + Vec2(cos(tmpAngle), sin(tmpAngle)) * 25;

			if (gm.bitmap->getBit(checkPos.x, checkPos.y))
			{
				gravity = 100;
				jumpSpeed = 0;
			}
		}

		while (gm.bitmap->getBit(tmpPos.x, tmpPos.y))
		{
			pos -= Vec2(cos(tmpAngle), sin(tmpAngle));
			tmpPos = center() + Vec2(cos(tmpAngle), sin(tmpAngle)) * 20;
		}
	}

}

void Player::moveUpdate(float dt)
{
	if (state != IDLE && state != MOVE) return;

	Vec2 moveDir = Vec2(0, 0);
	bool isMove = false;

	if (world.getKeyState('A') == 2)
	{
		moveDir.x = -1;
		scale.x = -1;
		frame->scale.x = bar->scale.x = -1;
		isMove = true;
	}
	if (world.getKeyState('D') == 2)
	{
		moveDir.x = 1;
		scale.x = 1;
		frame->scale.x = bar->scale.x = 1;
		isMove = true;
	}

	if (isMove)
	{
		pos += moveDir * speed * dt;

		particleTimer += dt;

		if (particleTimer > 0.3f)
		{
			Vec2 addPos = center() + Vec2(0, 20);
			Particle* p = gm.ingame->addParticle("image/Effect/walk/0.png", WALK, addPos);
			p->moveAngle = angle(gm.ingame->player->center(), addPos);
			particleTimer = 0;
		}
		changeState(MOVE);
	}
	else
	{
		changeState(IDLE); 
	}
}

void Player::jumpUpdate(float dt)
{
	if (onAir) return;

	if (world.getKeyState('H') == 1)
	{
		onAir = true;
		gravity = 0;
		jumpSpeed = 900;
	}
}

void Player::dieUpdate(float dt)
{
	if (state != DIE) return;

	if (!isDead)
	{
		gm.ingame->addEffect("image/character/die", 6, 12, center());
		Particle* p = gm.ingame->addParticle(play->texture, center());
		p->color.a = 1;
		p->fadeSpeed = 3;
		p->fadeIn = false;
		isDead = true;
	}
}

void Player::changeWeapon(WeaponType weaponType)
{
	if (weapon)
	{
		if (weapon->type == weaponType) return;

		removeChild(weapon);
	}

	weapon = new Weapon(weaponType);
	addChild(weapon);
	weapon->pos = Vec2(0, -18);
}

void Player::decreaseHp(int damage)
{
	Unit::decreaseHp(damage);
	DXUT_PlaySound(asset.sounds[L"sound/hit.wav"]);

	if (hp <= 0)
	{
		changeState(DIE);
		bar->visible = frame->visible = false;
	}
}
