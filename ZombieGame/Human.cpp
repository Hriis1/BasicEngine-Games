#include "Human.h"
#include <random>
#include <ctime>
#include<glm/gtx/rotate_vector.hpp>
#include <ResourceManager.h>

Human::Human()
	:_rotateFrames(0)
{

}
Human::~Human()
{

}

void Human::init(float speed, const glm::vec2& position)
{
	//Set the texture
	_textureID = BasicEngine::ResourceManager::getTexture("Textures/human.png").id;

	_health = 10;

	_speed = speed;
	_position = position;

	//Get random direction
	static std::mt19937 randomEngine((time(nullptr)));
	static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);
	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	//Make sure direction isn't 0
	if (_direction.length() == 0) _direction = glm::vec2(1.0f, 0.0f);
	//Normalize direction
	_direction = glm::normalize(_direction);
	
}

void Human::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime)
{
	//Update human movement
	_position += _direction * _speed * deltaTime;

	//Update the player direction randomly
	static std::mt19937 randomEngine((time(nullptr)));
	static std::uniform_real_distribution<float> randomRotate(-3.0f, 3.0f);

	//Rotate randomly every 100 frames
	_rotateFrames++;
	if(_rotateFrames % 100 == 0)
		_direction = glm::rotate(_direction, randomRotate(randomEngine));

	//Colide with world
	bool colliding  = colideWithLevel(levelData);

	//Rotate randomly if the human is colliding
	if (colliding)
		_direction = glm::rotate(_direction, randomRotate(randomEngine));
}


