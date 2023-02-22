#include "MainGame.h"
#include <SDL.h>

#include <iostream>

#include <BasicEngine.h>
#include <Timing.h>
#include <random>
#include <ctime>
#include<Errors.h>
#include "Gun.h"
#include<ResourceManager.h>
#include <glm/gtx/rotate_vector.hpp>

#include"Zombie.h"

MainGame::MainGame()
	: _screenWidth(1024), _screenHeight(768), _gameState(GameState::PLAY), _fps(0), _player(nullptr), _numHumansKilled(0), _numZombiesKilled(0)
{

}
MainGame::~MainGame()
{
	for (size_t i = 0; i < _levels.size(); i++)
		delete _levels[i];

	for (size_t i = 0; i < _humans.size(); i++)
		delete _humans[i];

	for (size_t i = 0; i < _zombies.size(); i++)
		delete _zombies[i];
}

void MainGame::initSystems()
{
	//Init the engine
	BasicEngine::init();

	//Init sound, must happen after BasicEngine::init()
	_audioEngine.init();

	//Create the window
	_window.createWindow("ZombieGame", _screenWidth, _screenHeight, 0);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	//Init the shaders
	initShaders();

	//Init the sprite batches
	_agentSpriteBatch.init();
	_hudSpriteBatch.init();

	//Init sprite fonts
	_spriteFont = new BasicEngine::SpriteFont("Fonts/chintzy.ttf",34);

	//Set up the cameras
	const float CAMERA_SCALE = 0.5f;
	_camera.init(_screenWidth, _screenHeight);
	_camera.setScale(0.5f);

	_HUDcamera.init(_screenWidth, _screenHeight);
	_HUDcamera.setPosition(glm::vec2(_screenWidth / 2.0f, _screenHeight/2.0f));

	//Init particles
	_bloodParticleBatch = new BasicEngine::ParticleBatch2D();
	_bloodParticleBatch->init(1000, 0.1f, BasicEngine::ResourceManager::getTexture("Textures/particle.png"),
		[](BasicEngine::Particle2D& p, float deltaTime)
		{
			p.position += p.velocity * deltaTime;
			p.color.a = (GLubyte)(p.life * 255);
		});
	_particleEngine.addParticleBatch(_bloodParticleBatch);

	
}

void MainGame::initLevel()
{
	//Level 1
	_levels.push_back(new Level("Levels/level2.txt"));
	_currentLevel = 0;

	//Init the player
	_player = new Player();
	_player->init(5.0f, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager, &_camera, &_bullets);

	_humans.push_back(_player);

	//Get random direction
	std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	static std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() -2);
	static std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

	
	//Add all humans
	for (size_t i = 0; i < _levels[_currentLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human);
		_humans.back()->init(HUMAN_SPEED, glm::vec2(randX(randomEngine) * TILE_WIDTH, randY(randomEngine)* TILE_WIDTH));
	}

	//Add the zombies
	
	const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->getStartZombilesPos();
	for (size_t i = 0; i < zombiePositions.size(); i++)
	{
		_zombies.push_back(new Zombie());
		_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
	}

	//Set up the players guns
	const float BULLET_SPEED = 20.0f;
	_player->AddGun(new Gun("Pistol", 10, 1, 0.0f, BULLET_SPEED, 5.0f, _audioEngine.loadSoundEffect("Sound/shots/pistol.wav")));
	_player->AddGun(new Gun("Shotgun", 30, 10, 0.5f, BULLET_SPEED, 3.0f, _audioEngine.loadSoundEffect("Sound/shots/shotgun.wav")));
}

void MainGame::initShaders()
{
	//Compile color shader
	_textureProgram.compileShaders("Shaders/colorShadingvert.txt", "Shaders/colorShadingfrag.txt");
	_textureProgram.addAttribute("vertexPosition");
	_textureProgram.addAttribute("vertexColor");
	_textureProgram.addAttribute("vertexUV");
	_textureProgram.linkShaders();

}

void MainGame::gameLoop()
{
	const float DESIRED_FPS = 60.0f;
	const int MAX_PHYSICS_STEPS = 6;

	BasicEngine::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(60.0f);

	

	const float MS_PER_SECOND = 1000;
	const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;
	const float MAX_DELTATIME = 1.0f;

	float prevTicks = SDL_GetTicks();


	while (_gameState == GameState::PLAY)
	{
		
		fpsLimiter.begin();

		float newTicks = SDL_GetTicks();
		float frameTime = newTicks - prevTicks;
		prevTicks = newTicks;
		float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

		checkVictory();

		_inputManager.update();

		processInput();

		int i = 0;
		while (totalDeltaTime > 0.0f && i<MAX_PHYSICS_STEPS)
		{
			float deltaTime = std::min(totalDeltaTime, MAX_DELTATIME);
			updateAgents(deltaTime);

			updateBullets(deltaTime);

			_particleEngine.update(deltaTime);

			totalDeltaTime -= deltaTime;
			i++;

		}
		
		_camera.setPosition(_player->getPosition());

		_camera.update();

		_HUDcamera.update();

		drawGame();

		_fps = fpsLimiter.end();

		std::cout << _fps << std::endl;
	}
}

void MainGame::updateAgents(float deltaTime)
{

	//Update all humans
	for (size_t i = 0; i < _humans.size(); i++)
	{
		_humans[i]->update(_levels[_currentLevel]->getLevelData(),_humans,_zombies, deltaTime);
	}

	//Update all zombies
	for (size_t i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies, deltaTime);
	}

	//Update Human collisions
	for (size_t i = 0; i < _humans.size(); i++)
	{
		for (size_t j = i+1; j < _humans.size(); j++)
		{
			_humans[i]->colideWithAgent(_humans[j]);
		}
	}
	//Update Zombie collisions
	for (size_t i = 0; i < _zombies.size(); i++)
	{
		//Colide with other zombies
		for (size_t j = i + 1; j < _zombies.size(); j++)
		{
			_zombies[i]->colideWithAgent(_zombies[j]);
		}
		//Colide with humans
		for (size_t j = 1; j < _humans.size(); j++)
		{
			if (_zombies[i]->colideWithAgent(_humans[j]))
			{
				//Turn the human into a zombie
				
				//Add the new Zombie
				_zombies.push_back(new Zombie);
				_zombies.back()->init(ZOMBIE_SPEED, _humans[j]->getPosition());

				//Delete the human
				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}
		}

		//Colide with the player
		if (_zombies[i]->colideWithAgent(_player))
		{
			std::cout << "Number of humans killed: " << _numHumansKilled << std::endl;
			std::cout << "Number of zombies killed: " << _numZombiesKilled << std::endl;
			std::cout << "Humans remaining: " << _humans.size() << std::endl;

			BasicEngine::fatalError("You lose!");
		}

	}

	
}

void MainGame::updateBullets(float deltaTime)
{
	//Update bullets and collide with world
	for (size_t i = 0; i < _bullets.size(); i)
	{
		//if update returns true it means the bullet is colliding with the world
		if (_bullets[i].update(_levels[_currentLevel]->getLevelData(), deltaTime))
		{
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
		else
		{
			i++;
		}
	}
	
	bool wasBulletRemoved = false;
	//Collide bullets with agents
	for (size_t i = 0; i < _bullets.size();i++)
	{
		wasBulletRemoved = false;
		//Collide with humans
		for (size_t j = 1; j < _humans.size();)
		{
			if (_bullets[i].collideWithAgents(_humans[j]))
			{
				//Add blood
				addBlood(_bullets[i].getPosition(), 7);

				//Damage the human
				if (_humans[j]->takeDMG(_bullets[i].getDMG()))
				{
					_numHumansKilled++;

					delete _humans[j];
					_humans[j] = _humans.back();
					_humans.pop_back();
				}

				_bullets[i] = _bullets.back();
				_bullets.pop_back();
				i--;
				wasBulletRemoved = true;
				break;
			}
			else
			{
				j++;
			}
		}

		if (wasBulletRemoved)
			continue;
		

		//Collidew with zombies
		for (size_t j = 0; j < _zombies.size();)
		{
			if (_bullets[i].collideWithAgents(_zombies[j]))
			{
				//Add blood
				addBlood(_bullets[i].getPosition(), 7);

				//Damage the zombie
				if (_zombies[j]->takeDMG(_bullets[i].getDMG()))
				{
					_numZombiesKilled++;

					delete _zombies[j];
					_zombies[j] = _zombies.back();
					_zombies.pop_back();
				}

				_bullets[i] = _bullets.back();
				_bullets.pop_back();
				i--; //Make sure we dont skip a bullet
				break;
			}
			else
			{
				j++;
			}
		}
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
				break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;

		}
	}
}

void MainGame::drawGame()
{
	//Set the base depth to 1.0
	glClearDepth(1.0);
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_textureProgram.use();

	//Draw code goes here
	glActiveTexture(GL_TEXTURE0);

	//Make sure the shader uses texture 0
	GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	//Grab the camera matrix
	glm::mat4 projectionMatrix = _camera.getCameraMatrix();
	GLint pUniform = _textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	//Draw the level
	_levels[_currentLevel]->draw();

	//Begin drawing agents
	_agentSpriteBatch.begin();

	//Draw all humans including the player
	for (size_t i = 0; i < _humans.size(); i++)
	{
		if (_camera.isBoxInView(_humans[i]->getPosition(), glm::vec2(AGENT_RADIUS * 2.0f)))
			_humans[i]->draw(_agentSpriteBatch);
	}

	//Draw all zombies
	for (int i = 0; i < _zombies.size(); i++)
	{
		if (_camera.isBoxInView(_zombies[i]->getPosition(), glm::vec2(AGENT_RADIUS * 2.0f)))
			_zombies[i]->draw(_agentSpriteBatch);
	}
	
	//Draw all bullets
	for (size_t i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_agentSpriteBatch);
	}

	_agentSpriteBatch.end();

	_agentSpriteBatch.renderBatch();

	//Draw particles
	_particleEngine.draw(&_agentSpriteBatch);

	//Draw the hud(which doesn't work)
	drawHud();

	_textureProgram.unuse();

	//Swap our buffer and draw everythong to the screen
	_window.swapBuffer();
}

void MainGame::drawHud()
{
	//Grab the camera matrix
	glm::mat4 projectionMatrix = _HUDcamera.getCameraMatrix();
	GLint pUniform = _textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	char buffer[256];

	_hudSpriteBatch.begin();

	sprintf_s(buffer, "Num Humans %d", _humans.size());

	_spriteFont->draw(_hudSpriteBatch, buffer, glm::vec2(0, 0), glm::vec2(1.0f), 0.0f, BasicEngine::Color(255, 122, 255, 255));

	_hudSpriteBatch.end();

	_hudSpriteBatch.renderBatch();

}

void MainGame::addBlood(const glm::vec2& position, int numParticles)
{
	static std::mt19937 randEngine(time(nullptr));
	static std::uniform_real_distribution<float> randAngle(0.0f, 2.0f * M_PI);
	glm::vec2 vel(10.1f, 0.0f);

	for (size_t i = 0; i < numParticles; i++)
	{
		_bloodParticleBatch->addParticle(position, glm::rotate(vel, randAngle(randEngine)), BasicEngine::Color(255, 0, 0, 255), 20.0f);
	}
	
}

void MainGame::checkVictory()
{
	if (_zombies.empty())
	{
		std::cout << "Number of humans killed: " << _numHumansKilled << std::endl;
		std::cout << "Number of zombies killed: " << _numZombiesKilled << std::endl;
		std::cout << "Humans remaining: " << _humans.size() - 1 << std::endl;

		BasicEngine::fatalError("You WIN!");
	}
}



void MainGame::run()
{
	initSystems();
	initLevel();

	BasicEngine::Music music = _audioEngine.loadMusic("Sound/XYZ.ogg");
	music.play(-1);

	gameLoop();
}
