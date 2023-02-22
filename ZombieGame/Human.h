#pragma once

#include "Agent.h"

class Human : public Agent
{
private:
	int _rotateFrames;
public:
	Human();
	virtual ~Human();

	void init(float speed, const glm::vec2& position);

	virtual void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime) override;

};

