#pragma once

#include <glm/glm.hpp>

#include <SpriteBatch.h>

class Bullet
{
private:
	int _lifeTime;
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
public:
	Bullet(const glm::vec2& pos, const glm::vec2& dir, float speed, int lifeTime);
	~Bullet();

	void draw(BasicEngine::SpriteBatch& spriteBatch);

	//Returns true when lifetime <= 0 (The bullet has to be destroied)
	bool update();
};

