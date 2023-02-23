#include "FileReadWriter.h"
#include <ImageLoader.h>

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

void FileReadWriter::loadLevelData(const std::string& filePath, b2World* world, Player*& player, std::vector<Box>& boxes, std::vector<BasicLight>& lights)
{
	std::fstream levelFile;
	levelFile.open(filePath, std::ios::in);
	if (levelFile.is_open())
	{
		{//Load the player
			glm::vec2 playerPosition(0.0f);
			glm::vec2 playerDrawDims(0.0f);
			glm::vec2 playerCollisionDims(0.0f);
			int r, g, b, a;//Color vals
			levelFile >> playerPosition.x >> playerPosition.y >> playerDrawDims.x >> playerDrawDims.y >> playerCollisionDims.x >> playerCollisionDims.y
				>> r >> g >> b >> a;

			player = new Player();
			BasicEngine::Color playerColor = BasicEngine::Color(r,g,b,a);
			player->init(world, playerPosition, playerDrawDims, playerCollisionDims, playerColor);
		}

		int boxesSize;
		levelFile >> boxesSize;
		boxes.resize(boxesSize);
		{//Load boxes
			glm::vec2 boxPosition;
			glm::vec2 boxDims;
			std::string textureFilePath;
			int r, g, b, a;//Color vals
			bool isFixedRotation;
			bool isDynamic;
			float angle;
			for (size_t i = 0; i < boxesSize; i++)
			{
				levelFile >> boxPosition.x >> boxPosition.y >> boxDims.x >> boxDims.y >> textureFilePath >> r >> g >> b >> a >> isFixedRotation >> isDynamic >> angle;

				glm::vec4 uvRect;
				uvRect.x = boxPosition.x;
				uvRect.y = boxPosition.y;
				uvRect.z = boxDims.x;
				uvRect.w = boxDims.y;
				BasicEngine::GLTexture boxTexture = BasicEngine::ImageLoader::loadPNG(textureFilePath);
				boxes[i].init(world, boxPosition, boxDims, boxTexture, BasicEngine::Color(r, g, b, a), isFixedRotation, isDynamic, angle, uvRect);

			}
		}

		int lightsSize;
		levelFile >> lightsSize;
		lights.resize(lightsSize);
		{//Load lights
			int r, g, b, a;//Color vals
			glm::vec2 lightPosition;
			float lightSize;
			for (size_t i = 0; i < lightsSize; i++)
			{
				levelFile >> r >> g >> b >> a >> lightPosition.x >> lightPosition.y >> lightSize;
				lights[i].init(BasicEngine::Color(r, g, b, a), lightPosition, lightSize);
			}
		}
	}

}

