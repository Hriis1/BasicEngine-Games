#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include<SpriteBatch.h>

class Human;
class Zombie;
class Agent;

const int BULLET_RADIUS = 5;

class Bullet
{
private:
	
	glm::vec2 _position;
	glm::vec2 _direction;
	float _damage;
	float _speed;
private:
	bool collideWithWorld(const std::vector<std::string>& levelData);
public:
	Bullet(glm::vec2 position, glm::vec2 direction, float damage,float speed);
	~Bullet();

	//Whenever update returns true - delete the bullet
	bool update(const std::vector<std::string>& levelData, float deltatime);

	void draw(BasicEngine::SpriteBatch& spriteBatch);

	bool collideWithAgents(Agent* agent);

	//Getters
	float getDMG() const { return _damage; }
	glm::vec2 getPosition() const { return _position; }
};

