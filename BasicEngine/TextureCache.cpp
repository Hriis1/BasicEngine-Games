#include "TextureCache.h"
#include "ImageLoader.h"

#include <iostream>
namespace BasicEngine {
	TextureCache::TextureCache()
	{

	}
	TextureCache::~TextureCache() = default;

	GLTexture TextureCache::getTexture(const std::string& texturePath)
	{
		auto mit = _textureMap.find(texturePath);
		if (mit == _textureMap.end())
		{
			//Load the texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//Insert the texture into the map
			_textureMap.insert(std::make_pair(texturePath, newTexture));

			//std::cout << "Loaded texture" << std::endl;
			return newTexture;

		}

		//std::cout << "Used cached texture" << std::endl;
		return mit->second;

	}
}