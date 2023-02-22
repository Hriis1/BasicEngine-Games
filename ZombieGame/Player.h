#pragma once

#include "Human.h"

#include <InputManager.h>
#include <vector>
#include <Camera2D.h>

#include "Bullet.h"

class Gun;

class Player : public Human
{
private:
	BasicEngine::InputManager* _inputManager;
	std::vector<Gun*> _guns;
	int _currentGunIdx;

	BasicEngine::Camera2D* _camera;

	std::vector<Bullet>* _bullets;
	
public:
	Player();
	~Player();

	void init(float speed, const glm::vec2& position, BasicEngine::InputManager* inputManager, BasicEngine::Camera2D* camera, std::vector<Bullet>* bullets);

	void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime) override;

	void AddGun(Gun* gun);
};

