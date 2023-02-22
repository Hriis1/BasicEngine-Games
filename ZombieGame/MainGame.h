#pragma once

#include <Window.h>
#include <GLSLProgram.h>
#include <Camera2D.h>
#include <InputManager.h>
#include <ResourceManager.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <AudioEngine.h>
#include <ParticleEngine2D.h>
#include <ParticleBatch2D.h>

#include "Level.h"
#include "Player.h"
#include "Bullet.h"

class Zombie;

enum class GameState
{
	PLAY,EXIT
};

class MainGame
{
private:
	//Constants
	const float HUMAN_SPEED = 2.0f;
	const float ZOMBIE_SPEED = 2.5f;

	//Member variables
	BasicEngine::Window _window; //The game window
		
	BasicEngine::GLSLProgram _textureProgram; //The shader program

	BasicEngine::InputManager _inputManager; //Handles input

	BasicEngine::Camera2D _camera; //Main camera
	BasicEngine::Camera2D _HUDcamera; //A camera for the hud

	BasicEngine::SpriteBatch _agentSpriteBatch; //Draws all agents;

	BasicEngine::SpriteBatch _hudSpriteBatch; //Draws text

	BasicEngine::ParticleEngine2D _particleEngine;
	BasicEngine::ParticleBatch2D* _bloodParticleBatch;

	std::vector<Level*> _levels; //Vector of all levels

	int _screenWidth, _screenHeight;

	float _fps;

	int _currentLevel;

	std::vector<Human*> _humans; //vector of all humans
	std::vector<Zombie*> _zombies; //vector of all zombies
	std::vector<Bullet> _bullets; //vector of all bullets

	Player* _player;

	GameState _gameState;

	BasicEngine::SpriteFont* _spriteFont;

	BasicEngine::AudioEngine _audioEngine;

	//Stats
	int _numHumansKilled; //Humans killed by the player
	int _numZombiesKilled; //Zombies killed by the player
private:
	//Init core systems;
	void initSystems();

	//Init the level and sets up everything
	void initLevel();

	//Init shaders
	void initShaders();

	//Main game loop for the program
	void gameLoop();

	//Updates all agents
	void updateAgents(float deltaTime);

	//Updates all bullets
	void updateBullets(float deltaTime);

	//Handles input processing
	void processInput();

	//Renders the game
	void drawGame();
	
	//Draws the HUD
	void drawHud();

	//Adds blood to the particle engine
	void addBlood(const glm::vec2& position, int numParticles);

	//Checks for victory
	void checkVictory();


public:

	MainGame();
	~MainGame();

	//Runs the game
	void run();

};

