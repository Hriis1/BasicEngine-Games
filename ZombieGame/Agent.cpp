#include "Agent.h"

#include <ResourceManager.h>
#include "Level.h"

#include <algorithm>

Agent::Agent()
{

}
Agent::~Agent()
{

}

void Agent::checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePositions, float x, float y)
{
	if (isnan(x) || isnan(y))
	{
		return;
	}
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH), floor(y / (float)TILE_WIDTH));
	int Ugax = cornerPos.x;
	int Bugay = cornerPos.y;

	//If the agent is outside of the world just return
	if (cornerPos.x < 0 || cornerPos.x >= levelData[1].size() || cornerPos.y < 0 || cornerPos.y >= levelData.size())
	{
		return;
	}
	if (levelData[cornerPos.y][cornerPos.x] != '.')
		collideTilePositions.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH/2.0f));
}

//AABB collision
void Agent::collideWithTile(glm::vec2 tilePos)
{
	
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 centerPlayerPos = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPlayerPos - tilePos;

	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);

	//If this is true we are colliding
	if (xDepth > 0 && yDepth > 0)
	{
		if (std::max(xDepth,0.0f) < std::max(yDepth,0.0f))
		{
			if(distVec.x > 0)
				_position.x += xDepth;
			else
				_position.x -= xDepth;
		}
		else
		{
			if (distVec.y > 0.0f)
				_position.y += yDepth;
			else
				_position.y -= yDepth;
		}
	}
}

bool Agent::colideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePositions;

	//Check the four corners

	//1st corner
	checkTilePosition(levelData, collideTilePositions,_position.x, _position.y);
	//2nd corner
	checkTilePosition(levelData, collideTilePositions, _position.x + AGENT_WIDTH, _position.y);
	//3rd corner
	checkTilePosition(levelData, collideTilePositions, _position.x, _position.y + AGENT_WIDTH);
	//4th corner
	checkTilePosition(levelData, collideTilePositions, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH);


	//Do the collision
	for (size_t i = 0; i < collideTilePositions.size(); i++)
		collideWithTile(collideTilePositions[i]);

	if (collideTilePositions.size() != 0)
		return true;
	else
		return false;
}

bool Agent::colideWithAgent(Agent* otherAgent)
{
	const float MIN_DISTANCE = (AGENT_RADIUS-4) * 2;
	//Get the positions of both agents
	glm::vec2 centerPosA = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 centerPosB = otherAgent->getPosition() + glm::vec2(AGENT_RADIUS);

	//Get the vector between them
	glm::vec2 distVect = centerPosA - centerPosB;
	//Get the distance of the vector
	float distance = glm::length(distVect);
	//Get the collision depth
	float collisionDepth = MIN_DISTANCE - distance;
	//Check for collision
	if (collisionDepth > 0)
	{
		//The amount and direction the colliding agants should be pushed by
		glm::vec2 collisionDepthVec = glm::normalize(distVect) * collisionDepth;

		_position += collisionDepthVec / 2.0f;
		otherAgent->_position -= collisionDepthVec / 2.0f;
		return true;
	}
	return false;

}
	

void Agent::draw(BasicEngine::SpriteBatch& spriteBatch)
{

	const glm::vec4 uvRect(0.0f,0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;


	spriteBatch.draw(destRect, uvRect, _textureID, 0.0f, _color, _direction);
}

bool Agent::takeDMG(float dmg)
{
	_health -= dmg;

	return(_health <= 0);
}
