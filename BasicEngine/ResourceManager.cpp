#include "ResourceManager.h"
namespace BasicEngine {
	TextureCache ResourceManager::_textureCache;

	GLTexture ResourceManager::getTexture(const std::string& texturePath)
	{
		return _textureCache.getTexture(texturePath);
	}
}

