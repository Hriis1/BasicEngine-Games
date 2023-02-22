#include "Capsule.h"

void Capsule::init(b2World* world, const glm::vec2& pos, const glm::vec2& dimensions, float density, float friction, bool fixedRotation)
{
	//Set the parameters
	_dimensions = dimensions;

	//Make the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.fixedRotation = fixedRotation;
	_body = world->CreateBody(&bodyDef);

	//Create the box
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f, (dimensions.y - dimensions.x) / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;

	_fixtures[0] = _body->CreateFixture(&fixtureDef);

	//Create the circles
	b2CircleShape circleShape;
	circleShape.m_radius = dimensions.x / 2.0f;

	b2FixtureDef circleDef;
	circleDef.shape = &circleShape;
	circleDef.density = density;
	circleDef.friction = friction;

	//Bottom circle
	circleShape.m_p.Set(0.0f, (-_dimensions.y + dimensions.x) / 2.0f);
	_fixtures[1] = _body->CreateFixture(&circleDef);

	//Top circle
	circleShape.m_p.Set(0.0f, (_dimensions.y - dimensions.x) / 2.0f);
	_fixtures[2] = _body->CreateFixture(&circleDef);
}

void Capsule::destroy(b2World* world)
{
	world->DestroyBody(_body);
}

void Capsule::drawDebug(BasicEngine::DebugRenderer& debugRenderer)
{
	static BasicEngine::Color color(255, 255, 255, 255);
	//Draw box
	glm::vec4 destRect;
	destRect.x = _body->GetPosition().x - _dimensions.x / 2.0f;
	destRect.y = _body->GetPosition().y - (_dimensions.y - _dimensions.x) / 2.0f;
	destRect.z = _dimensions.x;
	destRect.w = _dimensions.y - _dimensions.x;
	debugRenderer.drawBox(destRect, color, _body->GetAngle());

	//Draw circles

	//Bottom circle
	debugRenderer.drawCircle(glm::vec2(destRect.x + _dimensions.x /2.0f, destRect.y), color, _dimensions.x/2.0f);
	//Top Circle
	debugRenderer.drawCircle(glm::vec2(destRect.x + _dimensions.x / 2.0f, destRect.y + destRect.w), color, _dimensions.x / 2.0f);
}
