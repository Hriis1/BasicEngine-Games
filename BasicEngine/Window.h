#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <string>

namespace BasicEngine {
	enum WindowFlags
	{
		INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4
	};

	class Window
	{
	private:
		SDL_Window* _sdlWindow;
		int _screenWidth;
		int _screenHeight;

	public:
		Window();
		~Window();

		int createWindow(const std::string& windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		void swapBuffer();

		int getScreenWidth() { return _screenWidth; }
		int getScreenHeight() { return _screenHeight; }
	};

}