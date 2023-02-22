#include "App.h"
#include <ScreenList.h>

App::App()
{
}

App::~App()
{
}

void App::onInit()
{
}

void App::addScreens()
{
	_mainMenuScreen = std::make_unique<MainMenuScreeen>(&_window);
	_gameplayScreen = std::make_unique<GameplayScreen>(&_window);
	_levelEditorScreen = std::make_unique<EditorScreen>(&_window);

	_screenList->addScreen(_mainMenuScreen.get());
	_screenList->addScreen(_gameplayScreen.get());
	_screenList->addScreen(_levelEditorScreen.get());

	_screenList->setScreen(_mainMenuScreen->getScreenIndex());
}

void App::onExit()
{
}
