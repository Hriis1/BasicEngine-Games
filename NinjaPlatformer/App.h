#pragma once
#include <memory>
#include <IMainGame.h>

#include "GameplayScreen.h"
#include "MainMenuScreeen.h"
#include "EditorScreen.h"

class App : public BasicEngine::IMainGame
{
public:
	App();
	virtual ~App();

	//Called on initialization
	virtual void onInit() override;
	//For adding all screens
	virtual void addScreens() override;
	//Called when exiting
	virtual void onExit() override;

private:
	std::unique_ptr<MainMenuScreeen> _mainMenuScreen = nullptr;
	std::unique_ptr<GameplayScreen> _gameplayScreen = nullptr;
	std::unique_ptr<EditorScreen> _levelEditorScreen = nullptr;
};

