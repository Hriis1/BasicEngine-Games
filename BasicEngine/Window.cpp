#include "Window.h"

#include "Errors.h"

namespace BasicEngine {
	Window::Window()
	{

	}
	Window::~Window()
	{

	}

	int Window::createWindow(const std::string& windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;

		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		//Init window
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		if (_sdlWindow == nullptr)
			fatalError("SDL window could not be created");


		//Create an OpenGL context
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr)
			fatalError("SDL_GL context could not be created");

		//Init glew
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
			fatalError("Could not init glew");

		//Print the OpenGL version
		std::printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

		//Set the clear color
		glClearColor(0.0f, 0.0f, 1.0f, 1.0);

		//set VSync   1 = on, 0 = off
		SDL_GL_SetSwapInterval(0);

		//Enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}
}
