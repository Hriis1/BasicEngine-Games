#pragma once

#include "TextureCache.h"

#include <string>
namespace BasicEngine {
	class ResourceManager
	{
	private:
		static TextureCache _textureCache;
	public:
		static GLTexture getTexture(const std::string& texturePath);

	};
}

