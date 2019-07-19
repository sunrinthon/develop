#include "DXUT.h"
#include "Particle.h"


Particle::Particle(string path, ParticleType type)
{
	setPath(path);

	init(type);
}

Particle::Particle(Texture * texture, ParticleType type)
{
	this->texture = texture;

	rect = visibleRect = Rect(0, 0, texture->info.Width, texture->info.Height);

	init(type);
}

Particle::~Particle()
{
}

void Particle::init(ParticleType type)
{
	this->type = type;

	scaleCenter = rotationCenter = rect.center();

	if (type == FADE)
	{
		fadeSpeed = 3;
		maxAlpha = 3;
		fadeIn = true;
		speed = 0;
	}

	else if (type == STAR)
	{
		scale = Vec2(1, 1) * random(0.3f, 1.f);
		color.a = random(0.5f, 1.2f);
		rotation = D3DXToRadian(random(0, 360));
		rotationSpeed = random(-5.f, 5.f);
		speed = 70;
	}

	else if (type == MILLING)
	{
		scale = Vec2(1, 1) * random(0.3f, 1.f);
		color.a = random(0.5f, 1.2f);

		if (random(0, 1))
			rotation = D3DXToRadian(0);
		else
			rotation = D3DXToRadian(360);

		rotationSpeed = random(-5.f, 5.f);
		speed = 70;
		jumpSpeed = 300;
		gravity = 0;
	}

	else if (type == WALK)
	{
		scale *= 0.5f;
	}
	else if (type == FIRE)
	{
		scale = Vec2(1, 1) * random(0.4f, 1.3f);
		speed = random(30, 60);
	}
}

void Particle::update(float dt)
{
	if (type == FADE)
	{
		pos += Vec2(cos(moveAngle), sin(moveAngle)) * speed * dt;

		if (fadeIn)
		{
			color.a += fadeSpeed * dt;

			if (color.a > maxAlpha)
			{
				fadeIn = false;
			}
		}
		else
		{
			color.a -= fadeSpeed * dt;

			if (color.a < 0)
			{
				deleting = true;
			}
		}

	}

	else if (type == STAR)
	{
		color.a -= dt;

		rotation += rotationSpeed * dt;

		pos += Vec2(cos(moveAngle), sin(moveAngle)) * speed * dt;

		if (color.a < 0)
		{
			deleting = true;
		}
	}

	else if (type == MILLING)
	{
		color.a -= dt;

		pos.x += 50 * moveAngle * dt;
		gravity += 600 * dt;

		pos.y -= (jumpSpeed - gravity) * dt;

		if (color.a < 0)
		{
			deleting = true;
		}

	}

	else if (type == WALK)
	{
		scale.x -= dt;
		scale.y -= dt;

		if (scale.x < 0)
			deleting = true;
	}

	else if (type == FIRE)
	{
		pos.y -= speed * dt;

		scale.x -= dt;
		scale.y -= dt;

		if (scale.x < 0)
		{
			deleting = true;
		}
	}
}