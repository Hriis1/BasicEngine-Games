#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <SDL.h>
#include <GL/glew.h>

#include <BasicEngine.h>
#include <Sprite.h>
#include <GLSLProgram.h>
#include <GLTexture.h>
#include <Window.h>
#include <Camera2D.h>
#include <SpriteBatch.h>
#include <InputManager.h>
#include <Timing.h>

#include "Bullet.h"

enum class GameState
{
	PLAY,EXIT
};

class MainGame
{
private:
	BasicEngine::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	BasicEngine::GLSLProgram _colorProgram;

	BasicEngine::Camera2D _camera;

	BasicEngine::SpriteBatch _spriteBatch;

	BasicEngine::InputManager _inputManager;

	BasicEngine::FpsLimiter _fpsLimiter;

	std::vector<Bullet> _bullets;

	float _time;

	float _fps;
	float _MAX_FPS;

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
public:
	MainGame();
	~MainGame();

	void Run();

	
};

