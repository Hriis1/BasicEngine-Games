#pragma once
#include "GLTexture.h"

#include <glm/glm.hpp>

namespace BasicEngine
{
	class TileSheet
	{
	public:
		void init(const GLTexture& i_texture, const glm::ivec2& i_tileDims)
		{
			texture = i_texture;
			dims = i_tileDims;
		}

		glm::vec4 getUVs(int index)
		{
			int xTile = index % dims.x;
			int yTile = index / dims.x;

			glm::vec4 uvs;
			uvs.x = xTile / (float)dims.x;
			uvs.y = yTile / (float)dims.y;
			uvs.z = 1.0f / dims.x;
			uvs.w = 1.0f / dims.y;

			return uvs;
		}

		GLTexture texture;
		glm::ivec2 dims;
	};

}