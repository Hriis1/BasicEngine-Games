#include "Player.h"
#include <ResourceManager.h>
#include <SDL/SDL.h>
#include <iostream>

Player::Player()
{

}
Player::~Player()
{

}

void Player::init(b2World* world, const glm::vec2& pos, const glm::vec2& drawDims, const glm::vec2& collisionDims, const BasicEngine::Color& color)
{
	BasicEngine::GLTexture texture = BasicEngine::ResourceManager::getTexture("Assets/blue_ninja.png");
	_color = color;
	_drawDims = drawDims;
	_colisionDims = collisionDims;

	_capsule.init(world, pos, collisionDims,1.0f, 0.1f ,true);

	_texture.init(texture, glm::ivec2(10, 2));
}

void Player::destroy(b2World* world)
{
	_capsule.destroy(world);
}

void Player::draw(BasicEngine::SpriteBatch& spriteBatch)
{
	b2Body* _body = _capsule.getBody();
	glm::vec4 destRect((_body->GetPosition().x - (_drawDims.x / 2.0f)), (_body->GetPosition().y - (_capsule.getDimensions().y / 2.0f)), _drawDims.x, _drawDims.y);


	//Calculate animation
	glm::vec4 playerUVrect;
	int tileIdx = -1;
	int numTiles;

	float animSpeed = 0.2f;
	glm::vec2 velocity(_capsule.getBody()->GetLinearVelocity().x, _capsule.getBody()->GetLinearVelocity().y);

	if (_onGround)
	{
		//Player is on the ground
		if (_attacking)
		{
			//Player is attacking on the ground
			numTiles = 4;
			tileIdx = 1;
			if (_moveState != PlayerMoveState::ATTACKING)
			{
				//Reset the _animTime if the player starts attacking
				_moveState = PlayerMoveState::ATTACKING;
				_animTime = 0.0f;
			}
		}
		else if (abs(velocity.x) > 1.0f && ((velocity.x > 0 && _direction == 1 ) || (velocity.x < 0 && _direction == -1)))
		{
			//Running
			numTiles = 6;
			tileIdx = 10;

			//Take the velocity into account for the running animation
			animSpeed = abs(velocity.x) * 0.02f;

			if (_moveState != PlayerMoveState::RUNNING)
			{
				//Reset the _animTime if the player starts running
				_moveState = PlayerMoveState::RUNNING;
				_animTime = 0.0f;
			}
		}
		else
		{
			//Standing still
			_moveState = PlayerMoveState::STANDING;
			numTiles = 1;
			tileIdx = 0;
		}
	}
	else
	{
		//Player is jumping
		if (_attacking)
		{
			//Player is attacking in thr air
			numTiles = 1;
			tileIdx = 18;
			_moveState = PlayerMoveState::ATTACKING;
		}
		else if (abs(velocity.x) > 14)
		{
			//Player is in air but is moving fast in the x axis
			numTiles = 1;
			tileIdx = 10;
			_moveState = PlayerMoveState::IN_AIR;
		}
		else if (velocity.y > 0)
		{
			//Player is rising up
			numTiles = 1;
			tileIdx = 16;
			_moveState = PlayerMoveState::IN_AIR;
		}
		else
		{
			//Player is falling down
			numTiles = 1;
			tileIdx = 17;
			_moveState = PlayerMoveState::IN_AIR;
		}
	}

	//Increment animation time
	_animTime += animSpeed;

	//Check for attack end
	if (_animTime > numTiles)
		_attacking = false;

	//Apply animation
	tileIdx += (int)_animTime % numTiles;

	playerUVrect = _texture.getUVs(tileIdx);

	if (_direction == -1)
	{
		//Flip the sprite if we are looking left
		playerUVrect.x += 1.0f / _texture.dims.x;
		playerUVrect.z *= -1;
	}
	
	//Draw the player
	spriteBatch.draw(destRect, playerUVrect, _texture.texture.id, 0.0f, _color, _body->GetAngle());
}

void Player::drawDebug(BasicEngine::DebugRenderer& debugRenderer)
{
	_capsule.drawDebug(debugRenderer);
}

void Player::update(BasicEngine::InputManager& inputManager)
{
	b2Body* body = _capsule.getBody();

	//Check for movement
	if (inputManager.isKeyDown(SDLK_a)) {
		body->ApplyForceToCenter(b2Vec2(-100.0f, 0.0f), true);
		_direction = -1;
	}
	else if (inputManager.isKeyDown(SDLK_d)) {
		_direction = 1;
		body->ApplyForceToCenter(b2Vec2(100.0f, 0.0f), true);
	}
	else
	{
		//Apply damping
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x * 0.95f, body->GetLinearVelocity().y));
	}

	//Check if the player is attacking
	if (inputManager.isKeyDown(SDLK_SPACE))
		_attacking = true;
	
	//Limit max speed
	const float MAX_SPEED = 14.0f;
	if (body->GetLinearVelocity().x < -MAX_SPEED)
	{
		body->SetLinearVelocity(b2Vec2(-MAX_SPEED, body->GetLinearVelocity().y));
	}
	else if (body->GetLinearVelocity().x > MAX_SPEED)
	{
		body->SetLinearVelocity(b2Vec2(MAX_SPEED, body->GetLinearVelocity().y));
	}

	//Loop through all the contact points of player to determine if we can jump or not
	_onGround = false;
	for (b2ContactEdge* ce = body->GetContactList(); ce != nullptr; ce = ce->next)
	{
		b2Contact* c = ce->contact;
		if (c->IsTouching())
		{
			b2WorldManifold manifold;
			c->GetWorldManifold(&manifold);
			//Check if the points are below
			bool below = false;
			for (size_t i = 0; i < b2_maxManifoldPoints; i++)
			{
				if (manifold.points[i].y < body->GetPosition().y - _capsule.getDimensions().y / 2.0f + _capsule.getDimensions().x / 2.0f + 0.01f)
				{
					below = true;
					break;
				}
			}
			if (below)
			{
				_onGround = true;
				//Can jump
				if (inputManager.isKeyPressed(SDLK_w)) {
					body->ApplyLinearImpulse(b2Vec2(0.0f, 40.0f), b2Vec2(0.0f, 0.0f), true);
					break;
				}
			}
		}
	}
}
