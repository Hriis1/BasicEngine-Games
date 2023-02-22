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

};

