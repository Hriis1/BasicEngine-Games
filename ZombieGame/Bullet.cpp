#include "Bullet.h"
#include <ResourceManager.h>
#include <Vertex.h>
#include "Agent.h"
#include "Human.h"
#include "Zombie.h"
#include "Level.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed)
	: _position(position), _direction(direction),_damage(damage), _speed(speed)
{

}
Bullet::~Bullet()
{

}

bool Bullet::update(const std::vector<std::string>& levelData, float deltatime)
{
	_position += _direction * _speed * deltatime;

	return collideWithWorld(levelData);
}

void Bullet::draw(BasicEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 destRect(_position.x + BULLET_RADIUS, _position.y + BULLET_RADIUS, BULLET_RADIUS * 2, BULLET_RADIUS * 2);
	const glm::vec4 UVrect(0, 0, 1, 1);
	static GLuint textureID = BasicEngine::ResourceManager::getTexture("Textures/circle.png").id;
	BasicEngine::Color color = { 0,0,0,255 };
	spriteBatch.draw(destRect, UVrect,textureID,0.0f,color);
}

bool Bullet::collideWithWorld(const std::vector<std::string>& levelData)
{
	glm::ivec2 gridPosition;
	gridPosition.x = floor(_position.x / (float)TILE_WIDTH);
	gridPosition.y = floor(_position.y / (float)TILE_WIDTH);

	//If the bullet is outside of the world just return
	if (gridPosition.x < 0 || gridPosition.x >= levelData[0].length() || gridPosition.y < 0 || gridPosition.y >= levelData.size())
	{
		return true;
	}

	return(levelData[gridPosition.y][gridPosition.x] != '.');
}

bool Bullet::collideWithAgents(Agent* agent)
{
	const float MIN_DISTANCE = (AGENT_RADIUS - 4) + BULLET_RADIUS;
	//Get the positions of both agents
	glm::vec2 centerPosA = _position + glm::vec2(BULLET_RADIUS);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	//Get the vector between them
	glm::vec2 distVect = centerPosA - centerPosB;
	//Get the distance of the vector
	float distance = glm::length(distVect);
	//Get the collision depth
	float collisionDepth = MIN_DISTANCE - distance;
	//Check for collision
	if (collisionDepth > 0)
	{
		return true;
	}
	return false;
}
