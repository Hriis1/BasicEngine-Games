#include "Box.h"

Box::Box()
{
}

Box::~Box()
{
}

void Box::init(b2World* world, const glm::vec2& pos, const glm::vec2& dimensions, const BasicEngine::GLTexture& texture, const BasicEngine::Color& color, bool fixedRotation,
	bool isDynamic, float angle, glm::vec4 uvRect)
{
	//Make the body
	b2BodyDef bodyDef;
	if (isDynamic) {
		bodyDef.type = b2_dynamicBody;
	}
	else {
		bodyDef.type = b2_staticBody;
	}
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.fixedRotation = fixedRotation;
	bodyDef.angle = angle;
	_body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	_fixture = _body->CreateFixture(&fixtureDef);

	//Set the parameters
	_dimensions = dimensions;
	_color = color;
	_texture = texture;
	_uvRect = uvRect;

}

void Box::destroy(b2World* world)
{
	world->DestroyBody(_body);
}

void Box::draw(BasicEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 destRect((_body->GetPosition().x - (_dimensions.x / 2.0f)), (_body->GetPosition().y - (_dimensions.y / 2.0f)), _dimensions.x, _dimensions.y);
	spriteBatch.draw(destRect, _uvRect, _texture.id, 0.0f, _color, _body->GetAngle());
}
