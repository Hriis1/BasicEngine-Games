#include "Zombie.h"
#include "Human.h"
#include <ResourceManager.h>

Zombie::Zombie()
{

}
Zombie::~Zombie()
{

}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans)
{
	Human* closestHuman = nullptr;
	float smallestDistance = 99999.0f;
	for (size_t i = 0; i < humans.size(); i++)
	{
		glm::vec2 distVec = humans[i]->getPosition() - _position;
		float distance = glm::length(distVec);

		if (distance < smallestDistance)
		{
			smallestDistance = distance;
			closestHuman = humans[i];
		}
	}

	return closestHuman;
}

void Zombie::init(float speed, const glm::vec2& position)
{
	//Set the texture
	_textureID = BasicEngine::ResourceManager::getTexture("Textures/zombie.png").id;

	_health = 50;
	_speed = speed;
	_position = position;
}

void Zombie::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime)
{
	//Move towards nearest human
	Human* closestHuman = getNearestHuman(humans);
	if (closestHuman != nullptr)
	{
		_direction = closestHuman->getPosition() - _position;
		_direction = glm::normalize(_direction);
		_position += _direction * _speed * deltaTime;
	}

	//Collide with the level
	colideWithLevel(levelData);
}
