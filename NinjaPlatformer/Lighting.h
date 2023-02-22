#pragma once
#include <Vertex.h>
#include <glm/glm.hpp>
#include <SpriteBatch.h>

class BasicLight
{
public:
	void init(const BasicEngine::Color& _color, const glm::vec2& _position, float _size)
	{
		color = _color;
		position = _position;
		size = _size;
	}

	void draw(BasicEngine::SpriteBatch& spriteBatch)
	{
		glm::vec4 destRect((position.x - (size / 2.0f)), (position.y - (size / 2.0f)), size, size);
		spriteBatch.draw(destRect, glm::vec4(-1.0f,-1.0f, 2.0f ,2.0f), 0, 0.0f, color,0.0f);
	}

	BasicEngine::Color color;
	glm::vec2 position;
	float size;

};
