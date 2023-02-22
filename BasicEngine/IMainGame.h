#pragma once
#include <memory>

#include "Window.h"
#include "BasicEngine.h"
#include "InputManager.h"

namespace BasicEngine
{
	class ScreenList;
	class IGameScreen;

	class IMainGame
	{
	private:

	protected:
		std::unique_ptr<ScreenList> _screenList = nullptr;
		IGameScreen* _currentScreen = nullptr;
		bool _isRunning = false;
		float _fps = 0.0f;
		Window _window;

	protected:
		bool init();
		bool initSystems();

		//Custom update function
		virtual void update();
		//Custom render function
		virtual void draw();

	public:
		InputManager inputManager;

	public:
		IMainGame();
		virtual ~IMainGame();

		void run();
		void exitGame();

		//Called on initialization
		virtual void onInit() = 0;
		//For adding all screens
		virtual void addScreens() = 0;
		//Called when exiting
		virtual void onExit() = 0;

		void onSDLEvent(SDL_Event& evnt);

		

		//getters
		const float getFps() const { return _fps; }
	};
}

