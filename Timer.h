#pragma once
#include "Define.h"
class Timer
{
public:
	Timer();
	~Timer();

	void reset(float duration, int count, bool autoStart = true);
	void update(float dt);

	function<void()> onTick;
	function<void()> onFinish;

	pair<float, float> duration;
	pair<int, int> count;

	bool removing;
	bool active;
};

