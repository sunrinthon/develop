#pragma once
#include "Entity.h"
#include "Timer.h"

class Scene :
	public Entity
{
public:
	Scene();
	~Scene();

	void follow(Entity* target, Vec2 offset = screenCenter);
	void unfollow();
	void shake(float duration, int count, float range);
	void update(float dt);

	Entity* followTarget;
	Vec2 offset;
	Timer* shakeTimer;
};
