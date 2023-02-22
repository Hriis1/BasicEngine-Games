#include "Level.h"

#include <fstream>
#include <iostream>

#include <Errors.h>

#include <ResourceManager.h>

Level::Level(const std::string& fileName)
{

	std::ifstream file;
	file.open(fileName);

	//Error checking
	if (file.fail())
	{
		BasicEngine::fatalError("Failed to open" + fileName);
	}

	//Throw away the first string in temp and load the number of humans
	std::string temp;
	file >> temp >> _numHumans;

	//Throw away the rest of the 1stline
	std::getline(file, temp);

	while (std::getline(file, temp))
	{
		_levelData.push_back(temp);
	}

	//Test print the level
	/*for (size_t i = 0; i < _levelData.size(); i++)
		std::cout << _levelData[i] << std::endl;*/

	_spriteBatch.init();
	_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	BasicEngine::Color whiteColor;
	whiteColor = { 255,255,255,255 };

	//Render all the tiles
	for (size_t y = 0; y < _levelData.size(); y++)
	{
		

		for (size_t x = 0; x < _levelData[y].size(); x++)
		{
			//Get the tile
			char tile = _levelData[y][x];

			//Get dest rect
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			//Process the tile
			switch (tile)
			{
			case 'B':
			case 'R':
				_spriteBatch.draw(destRect, uvRect,BasicEngine::ResourceManager::getTexture("Textures/BlueBrick.png").id, 0.0f, whiteColor);
				break;
			case 'G':
			case 'L':
				_spriteBatch.draw(destRect, uvRect, BasicEngine::ResourceManager::getTexture("Textures/GreenBrick.png").id, 0.0f, whiteColor);
				break;
			case '@':
				_levelData[y][x] = '.';
				_startPlayerPos.x = x * TILE_WIDTH;
				_startPlayerPos.y = y * TILE_WIDTH;
				break;
			case 'Z':
				_levelData[y][x] = '.';
				_zombieStartPositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
				break;
			case '.':
				break;
			default:
				std::cout << "Unexpected symbol " << tile << " at " << x << " " << y << std::endl;
				break;
			}
		}
	}

	_spriteBatch.end();
	
	

}
Level::~Level()
{

}

void Level::draw()
{
	_spriteBatch.renderBatch();
}
