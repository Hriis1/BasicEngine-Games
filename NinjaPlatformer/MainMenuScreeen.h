#pragma once

#include <IGameScreen.h>
#include <memory>
#include <vector>
#include <Camera2D.h>
#include <Window.h>
#include <GUI.h>

#include "ScreenIndices.h"

class MainMenuScreeen : public BasicEngine::IGameScreen
{
public:
	MainMenuScreeen(BasicEngine::Window* window);
	~MainMenuScreeen();

	// Inherited via IGameScreen
	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;
	virtual void build() override;
	virtual void destroy() override;
	virtual void onEntry() override;
	virtual void onExit() override;
	virtual void update() override;
	virtual void draw() override;

	void checkInput();

private:
	BasicEngine::Camera2D _camera;
	BasicEngine::Window* _window;

	int _nextScreenIdx = SCREEN_INDEX_NO_SCREEN;

	//UI stuff
	BasicEngine::GUI _gui;

private:
	void initUI();

	//Event funcs
	bool onPlayButtonClicked(const CEGUI::EventArgs& e);
	bool onEdditorButtonClicked(const CEGUI::EventArgs& e);
	bool onExitClicked(const CEGUI::EventArgs& e);
};

