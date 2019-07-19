#pragma once
#include "Sprite.h"

class Particle :
	public Sprite
{
public:
	Particle(string path, ParticleType type);
	Particle(Texture* texture, ParticleType type);
	~Particle();

	void init(ParticleType type);
	void update(float dt);

	ParticleType type;
	float speed;
	float moveAngle;

	float scaleSpeed;
	float rotationSpeed;
	float fadeSpeed;
	float maxAlpha;
	float gravity;
	float jumpSpeed;

	bool fadeIn;

	Vec2 targetPos;
};