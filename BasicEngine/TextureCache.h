#pragma once

#include <map>
#include <string>

#include "GLTexture.h"
namespace BasicEngine {
	class TextureCache
	{
	private:
		std::map<const std::string, GLTexture> _textureMap;
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(const std::string& texturePath);
	};

}