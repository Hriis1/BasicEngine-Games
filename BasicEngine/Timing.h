#pragma once

namespace BasicEngine
{
	class FpsLimiter
	{
	private:
		float _MAX_FPS;
		float _fps;
		float _frameTime;
		unsigned int _startTicks;

	private:
		void calculateFPS();

	public:
		FpsLimiter();

		void init(float targetFPS);

		void setMaxFPS(float targetFPS);

		void begin();
		//end() returns the current FPS
		float end();


	};
}
