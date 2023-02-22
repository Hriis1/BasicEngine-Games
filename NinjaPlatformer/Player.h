#pragma once
#include "Capsule.h";

#include <GLTexture.h>
#include <SpriteBatch.h>
#include <InputManager.h>
#include <TileSheet.h>

enum class PlayerMoveState
{
	STANDING, RUNNING, IN_AIR, ATTACKING
};

class Player
{
public:
	Player();
	~Player();

	void init(b2World* world, const glm::vec2& pos, const glm::vec2& drawDims, const glm::vec2& collisionDims, const BasicEngine::Color& color);
	void destroy(b2World* world);

	void draw(BasicEngine::SpriteBatch& spriteBatch);

	void drawDebug(BasicEngine::DebugRenderer& debugRenderer);

	void update(BasicEngine::InputManager& inputManager);

	//getters
	const Capsule& getCapsule() const { return _capsule; }
	glm::vec2 getPosition() const {
		glm::vec2 rv;
		rv.x = _capsule.getBody()->GetPosition().x;
		rv.y = _capsule.getBody()->GetPosition().y;
		return rv;
	}

private:
	glm::vec2 _drawDims;
	BasicEngine::TileSheet _texture;
	BasicEngine::Color _color;
	Capsule _capsule;

	//Animation stuff
	float _animTime = 0;

	PlayerMoveState _moveState = PlayerMoveState::STANDING;
	int _direction = 1; //1=right or -1=left
	bool _onGround = false;
	bool _attacking = false;
};

