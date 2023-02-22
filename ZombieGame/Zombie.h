#pragma once

#include "Agent.h"

class Zombie : public Agent
{
private:

private:
	Human* getNearestHuman(std::vector<Human*>& humans);

public:
	Zombie();
	~Zombie();

	void init(float speed, const glm::vec2& position);

	virtual void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime) override;
};

