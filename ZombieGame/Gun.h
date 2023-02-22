#pragma once
#include <string>
#include <glm/glm.hpp>
#include <vector>

#include <AudioEngine.h>

#include "Bullet.h"
class Gun
{
private:
	std::string _name; //The name of the gun

	int _fireRate; //Fire rate in terms of frames

	float _frameCounter;

	int _bulletsPerShot; //How many bullets are fired at a time

	float _spread; // Accuracy

	float _bulletSpeed; //The speed of the bullets

	float _bulletDmg; //The damage inflicted by the bullets

	BasicEngine::SoundEffect _fireSF; //The sound effects that plays when you shoot the gun

private:
	void fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bullets);
public:
	Gun(const std::string& name, int fireRate, int bulletsPerShot, float spread, float bulletSpeed, float bulletDmg, BasicEngine::SoundEffect fireSF);
	~Gun();

	void update(bool isMouseDown,const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets, float deltaTime);

	
};

