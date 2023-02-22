#include "Player.h"

#include <SDL.h>

#include "Gun.h"
#include <ResourceManager.h>


Player::Player()
	:_currentGunIdx(-1)
{

}
Player::~Player()
{
	for (size_t i = 0; i < _guns.size(); i++)
	{
		delete _guns[i];
	}
}

void Player::init(float speed, const glm::vec2& position, BasicEngine::InputManager* inputManager, BasicEngine::Camera2D* camera, std::vector<Bullet>* bullets)
{
	//Set the texture
	_textureID = BasicEngine::ResourceManager::getTexture("Textures/player.png").id;

	_health = 100;
	_speed = speed;
	_position = position;

	_inputManager = inputManager;

	_camera = camera;

	_bullets = bullets;
}

void Player::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime)
{
	if (_inputManager->isKeyDown(SDLK_w))
	{
		_position.y += _speed * deltaTime;
	}
	else if (_inputManager->isKeyDown(SDLK_s))
	{
		_position.y -= _speed * deltaTime;
	}
	if (_inputManager->isKeyDown(SDLK_d))
	{
		_position.x += _speed * deltaTime;
	}
	else if (_inputManager->isKeyDown(SDLK_a))
	{
		_position.x -= _speed * deltaTime;
	}

	if (_inputManager->isKeyDown(SDLK_1) && _guns.size() >= 1)
	{
		_currentGunIdx = 0;
	}
	else if (_inputManager->isKeyDown(SDLK_2) && _guns.size() >= 1)
	{
		_currentGunIdx = 1;
	}

	glm::vec2 playerCenterPosition = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 mouseCoords = _inputManager->getMouseCoords();
	mouseCoords = _camera->convertScreenToWorld(mouseCoords);
	_direction = mouseCoords - playerCenterPosition;
	_direction = glm::normalize(_direction);

	if (_currentGunIdx != -1)
	{
		

		_guns[_currentGunIdx]->update(_inputManager->isKeyDown(SDL_BUTTON_LEFT),playerCenterPosition, _direction, *_bullets, deltaTime);
	}

	colideWithLevel(levelData);
}

void Player::AddGun(Gun* gun)
{
	//Add the gun to the vector of guns
	_guns.push_back(gun);
	
	//If this is the first gun - equip it
	if (_currentGunIdx == -1)
	{
		_currentGunIdx = 0;

	}
}
