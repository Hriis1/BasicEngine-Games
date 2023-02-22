#include "Bullet.h"

#include <GLTexture.h>
#include <ResourceManager.h>

Bullet::Bullet(const glm::vec2& pos, const glm::vec2& dir, float speed, int lifeTime)
	: _position(pos), _direction(dir), _speed(speed), _lifeTime(lifeTime)
{

}
Bullet::~Bullet() = default;

void Bullet::draw(BasicEngine::SpriteBatch& spriteBatch)
{
	static BasicEngine::GLTexture texture = BasicEngine::ResourceManager::getTexture("Textures/JimmyJumpPack/PNG/CharacterRight_Standing.png");

	BasicEngine::Color color = { 255, 255,255,255 };
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 30.0f, 30.0f);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
}

bool Bullet::update()
{
	_position += _direction * _speed;

	_lifeTime--;
	if (_lifeTime <= 0)
		return true;

	return false;
}
