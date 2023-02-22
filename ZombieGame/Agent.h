#pragma once

#include <glm/glm.hpp>

#include <SpriteBatch.h>

#include <string>

const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Zombie;
class Human;

class Agent
{
private:

protected:
	glm::vec2 _position;
	glm::vec2 _direction = glm::vec2(1.0f, 0.0f);
	BasicEngine::Color _color = BasicEngine::Color(255,255,255,255);
	float _speed;
	float _health;
	GLuint _textureID;
	
protected:
	void checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePositions, float x, float y);

	void collideWithTile(glm::vec2 tilePos);

public:
	Agent();
	virtual ~Agent();

	virtual void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime) = 0;

	bool colideWithLevel(const std::vector<std::string>& levelData);

	bool colideWithAgent(Agent* otherAgent);

	void draw(BasicEngine::SpriteBatch& spriteBatch);

	//Return true if zombie is dead
	bool takeDMG(float dmg);

	//Getters
	glm::vec2 getPosition() const { return _position; }
};

