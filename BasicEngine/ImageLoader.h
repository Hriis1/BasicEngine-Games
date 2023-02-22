#pragma once

#include "GLTexture.h"

#include <string>
namespace BasicEngine {
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(const std::string& filePath);
	};
}

