#pragma once

#include <GL/glew.h>
#include <string>

#include "GLTexture.h"
namespace BasicEngine {
	class Sprite
	{
	private:

		float _x;
		float _y;
		float _width;
		float _height;

		GLuint _vboID;

		GLTexture _texture;

	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, const std::string& texturePath);

		void draw();
	};
}
