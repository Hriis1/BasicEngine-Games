#pragma once

#include <string>
#include <vector>

#include <SpriteBatch.h>

const int TILE_WIDTH = 64;

class Level
{
private:
	std::vector<std::string> _levelData;
	int _numHumans;

	BasicEngine::SpriteBatch _spriteBatch;

	glm::vec2 _startPlayerPos;
	std::vector<glm::vec2> _zombieStartPositions;

	int numHumans;

public:
	//Load the level
	Level(const std::string& fileName);
	~Level();

	void draw();

	//Getters
	glm::vec2 getStartPlayerPos() const { return _startPlayerPos; }
	const std::vector<glm::vec2>& getStartZombilesPos() const { return _zombieStartPositions; }
	const std::vector<std::string>& getLevelData() const { return _levelData; }
	int getNumHumans() const { return _numHumans; }
	int getWidth() const { return _levelData[0].size(); }
	int getHeight() const { return _levelData.size(); }
};

