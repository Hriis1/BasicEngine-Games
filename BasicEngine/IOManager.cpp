#include "IOManager.h"

#include <fstream>

namespace BasicEngine {
	bool IOManager::readFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}

		//seek to the end of the file
		file.seekg(0, std::ios::end);

		//Get the file size in bytes
		int fileSize = file.tellg();

		//seek to the begining of the file
		file.seekg(0, std::ios::beg);

		//Reduce the file size by any header bytes that might be present
		fileSize -= file.tellg();

		//Resize the buffer vector to the size of the file
		buffer.resize(fileSize);

		file.read((char*)&(buffer[0]), fileSize);

		file.close();

		return true;
	}
	bool IOManager::readFileToBuffer(const std::string& filePath, std::string& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}

		//seek to the end of the file
		file.seekg(0, std::ios::end);

		//Get the file size in bytes
		int fileSize = file.tellg();

		//seek to the begining of the file
		file.seekg(0, std::ios::beg);

		//Reduce the file size by any header bytes that might be present
		fileSize -= file.tellg();

		//Resize the buffer vector to the size of the file
		buffer.resize(fileSize);

		file.read((char*)&(buffer[0]), fileSize);

		file.close();

		return true;
	}
}