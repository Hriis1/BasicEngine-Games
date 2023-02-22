#include "Gun.h"
#include <random>
#include <ctime>
#include<glm/gtx/rotate_vector.hpp>

Gun::Gun(const std::string& name, int fireRate, int bulletsPerShot, float spread, float bulletSpeed, float bulletDmg, BasicEngine::SoundEffect fireSF)
	: _name(name), _fireRate(fireRate),_frameCounter(0), _bulletsPerShot(bulletsPerShot), _spread(spread), _bulletSpeed(bulletSpeed), _bulletDmg(bulletDmg),
	_fireSF(fireSF)
{
}
Gun::~Gun()
{

}

void Gun::fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bullets)
{
	//Play the sound effect
	_fireSF.play();

	static std::mt19937 randomEngine((time(nullptr)));
	std::uniform_real_distribution<float> randomRotate(-_spread, _spread);
	for (size_t i = 0; i < _bulletsPerShot; i++)
	{
		bullets.emplace_back(position, glm::rotate(direction,randomRotate(randomEngine)), _bulletDmg, _bulletSpeed);
	}
}

void Gun::update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets, float deltaTime)
{
	_frameCounter += 1.0f * deltaTime;
	if (_frameCounter >= _fireRate && isMouseDown)
	{
		//Fire the gun
		fire(direction,position, bullets);
		_frameCounter = 0;
	}
}
