#pragma once

#include <vector>
#include <string>
namespace BasicEngine {
	class IOManager
	{
	public:
		static bool readFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer);
		static bool readFileToBuffer(const std::string& filePath, std::string& buffer);
	};
}

