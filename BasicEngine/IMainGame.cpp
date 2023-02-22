#include "IMainGame.h"
#include "Timing.h"
#include "ScreenList.h"
#include "IGameScreen.h"

#include "Errors.h"

namespace BasicEngine {
	
	BasicEngine::IMainGame::IMainGame()
	{
		_screenList = std::make_unique<ScreenList>(this);
	}

	BasicEngine::IMainGame::~IMainGame()
	{
	}

	bool IMainGame::init()
	{
		BasicEngine::init();

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		if (!initSystems())
			return false;

		onInit();

		addScreens();
		_currentScreen = _screenList->getCurrent();
		_currentScreen->onEntry();
		_currentScreen->setRunning();

		return true;
	}

	bool IMainGame::initSystems()
	{
		_window.createWindow("Default", 1280, 720, 0);
		return true;
	}

	void IMainGame::update()
	{
		if (_currentScreen)
		{
			switch (_currentScreen->getState())
			{
			case ScreenState::RUNNING:
				_currentScreen->update();
				break;
			case ScreenState::CHANGE_NEXT:
				_currentScreen->onExit();
				_currentScreen = _screenList->moveNext();
				if (_currentScreen) {
					_currentScreen->setRunning();
					_currentScreen->onEntry();
				}
				break;
			case ScreenState::CHENG_PREVIOUS:
				_currentScreen->onExit();
				_currentScreen = _screenList->movePrevious();
				if (_currentScreen) {
					_currentScreen->setRunning();
					_currentScreen->onEntry();
				}
				break;
			case ScreenState::EXIT_APPLICATION:
				exitGame();
				break;
			default:
				break;
			}
		}
		else
		{
			exitGame();
		}
	}

	void IMainGame::draw()
	{
		glViewport(0, 0, _window.getScreenWidth(), _window.getScreenHeight());
		if (_currentScreen && _currentScreen->getState() == ScreenState::RUNNING)
			_currentScreen->draw();
	}

	void IMainGame::onSDLEvent(SDL_Event& evnt)
	{
		switch (evnt.type) {
		case SDL_QUIT:
			exitGame();
			break;
		case SDL_MOUSEMOTION:
			inputManager.setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			inputManager.releaseKey(evnt.button.button);
			break;
		}
	}

	void IMainGame::run()
	{
		if (!init()) return;

		FpsLimiter limiter;
		limiter.setMaxFPS(60.0f);

		_isRunning = true;
		while (_isRunning)
		{
			limiter.begin();

			inputManager.update();
			update();
			if (_isRunning)
			{
				draw();

				_fps = limiter.end();
				_window.swapBuffer();
			}
		}
	}

	void IMainGame::exitGame()
	{
		_currentScreen->onExit();

		if (_screenList)
		{
			_screenList->destroy();
			_screenList.reset();
		}

		_isRunning = false;

	}

}
