#pragma once
#include "Player.h"
#include "Box.h"
#include "Lighting.h"

#include<fstream>
#include<vector>
#include <string>

class FileReadWriter
{
public:
	static void writeLevelData(const std::string& filePath, Player* player, const std::vector<Box>& boxes, const std::vector<BasicLight>& lights);

	//Before loading data the containers and player variable must be cleared
	static void loadLevelData(const std::string& filePath, b2World* world, Player*& player, std::vector<Box>& boxes, std::vector<BasicLight>& lights);

};

