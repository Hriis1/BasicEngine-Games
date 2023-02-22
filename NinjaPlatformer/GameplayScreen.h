#pragma once
#include <IGameScreen.h>
#include <box2d/box2d.h>
#include <memory>
#include <vector>
#include <SpriteBatch.h>
#include <GLSLProgram.h>
#include <Camera2D.h>
#include <Window.h>
#include <GLTexture.h>
#include <DebugRenderer.h>
#include <GUI.h>

#include "Box.h"
#include "Player.h"

class GameplayScreen : public BasicEngine::IGameScreen
{
public:
	GameplayScreen(BasicEngine::Window* window);
	virtual ~GameplayScreen();

	// Inherited via IGameScreen
	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;
	virtual void build() override;
	virtual void destroy() override;
	virtual void onEntry() override;
	virtual void onExit() override;
	virtual void update() override;
	virtual void draw() override;

private:
	BasicEngine::SpriteBatch _spriteBatch;
	BasicEngine::GLSLProgram _textureProgram;
	BasicEngine::GLSLProgram _lightProgram;
	BasicEngine::Camera2D _camera;
	BasicEngine::GLTexture _texture;
	BasicEngine::Window* _window;
	BasicEngine::DebugRenderer _debugRenderer;

	bool _renderDebug = false;

	std::unique_ptr<b2World> _world;
	std::vector<Box> _boxes;
	Player _player;

	//UI stuff
	BasicEngine::GUI _gui;
private:
	void checkInput();
	void initShaders();
	void initUI();

	//Event funcs
	bool onExitClicked(const CEGUI::EventArgs& e);

	
};

