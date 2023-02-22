#include "Timing.h"

#include <SDL/SDL.h>

namespace BasicEngine
{
	FpsLimiter::FpsLimiter()
	{

	}

	void FpsLimiter::init(float maxFPS)
	{
		setMaxFPS(maxFPS);
	}

	void FpsLimiter::setMaxFPS(float maxFPS)
	{
		_MAX_FPS = maxFPS;
	}

	void FpsLimiter::begin()
	{
		_startTicks = SDL_GetTicks();
	}

	float FpsLimiter::end()
	{
		calculateFPS();

		float frameTicks = SDL_GetTicks() - _startTicks;
		//Limit the fps to the _MAX_FPS
		if (1000.0f / _MAX_FPS > frameTicks)
		{
			SDL_Delay(1000.0f / _MAX_FPS - frameTicks);
		}

		return _fps;
	}

	void FpsLimiter::calculateFPS()
	{
		static const int NUM_SAMPLES = 10;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		static float prevTicks = SDL_GetTicks();

		float currentTicks;
		currentTicks = SDL_GetTicks();

		_frameTime = currentTicks - prevTicks;
		frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;
		prevTicks = currentTicks;

		int count;
		currentFrame++;
		if (currentFrame < NUM_SAMPLES)
			count = currentFrame;
		else
			count = NUM_SAMPLES;

		float frameTimeAvg = 0;
		for (size_t i = 0; i < count; i++)
		{
			frameTimeAvg += frameTimes[i];
		}
		frameTimeAvg /= count;

		if (frameTimeAvg > 0)
		{
			_fps = 1000.0f / frameTimeAvg;
		}
		else
		{
			_fps = 60.0f;
		}

		
	}
}