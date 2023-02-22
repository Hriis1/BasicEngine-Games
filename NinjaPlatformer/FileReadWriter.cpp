#include "FileReadWriter.h"

void FileReadWriter::writeLevelData(const std::string& filePath, Player* player, const std::vector<Box>& boxes, const std::vector<BasicLight>& lights)
{
	std::fstream levelFile;
	levelFile.open(filePath, std::ios::out);
	if (levelFile.is_open())
	{
		glm::vec2 playerPos = player->getPosition();

		//Write player data - 1st 2 lines
		levelFile << playerPos.x << " " << playerPos.y << '\n' << player->_drawDims.x << " " << player->_drawDims.y << " " << player->_colisionDims.x << " " << player->_colisionDims.y << " "
			<< (int)player->_color.r << " " << (int)player->_color.g << " " << (int)player->_color.b << " " << (int)player->_color.a
			<<'\n';

		//Write number of boxes - 3rd line
		levelFile << boxes.size() << '\n';

		//Write boxes data - next boxes.size() lines
		for (size_t i = 0; i < boxes.size(); i++)
		{
			levelFile << boxes[i].getPosition().x << " " << boxes[i].getPosition().y << " " << boxes[i]._dimensions.x << " " << boxes[i]._dimensions.y
				<< " " << boxes[i]._texture.filePath << " " << (int)boxes[i]._color.r <<" "<<(int)boxes[i]._color.g << " " << (int)boxes[i]._color.b << " " << (int)boxes[i]._color.a
				<< " " << boxes[i]._body->IsFixedRotation() <<" "<< (boxes[i]._body->GetType() == b2BodyType::b2_dynamicBody) << " " << boxes[i]._body->GetAngle() << '\n';
		}

		//Write number of lights - next line
		levelFile << lights.size() << '\n';

		//Write lights data - next lights.size() lines
		for (size_t i = 0; i < lights.size(); i++)
		{
			levelFile << (int)lights[i].color.r << " " << (int)lights[i].color.g << " " << (int)lights[i].color.b << " " << (int)lights[i].color.a
				<< " " << lights[i].position.x << " " << lights[i].position.y << " " << lights[i].size << '\n';
		}

	}
}
