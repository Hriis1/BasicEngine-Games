#pragma once
#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <Vertex.h>
#include <GLTexture.h>
#include <SpriteBatch.h>

class Box
{
	friend class FileReadWriter;

public:
	Box();
	~Box();

	void init(b2World* world, const glm::vec2& pos, const glm::vec2& dimensions, const BasicEngine::GLTexture& texture, const BasicEngine::Color& color, bool fixedRotation,
		bool isDynamic, float angle = 0.0f,glm::vec4 uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	void destroy(b2World* world);

	void draw(BasicEngine::SpriteBatch& spriteBatch);

	bool isDynamic() const { return _body->GetType() == b2_dynamicBody; }

	//test if a point is inside the box
	bool testPoint(float x, float y) const { return _fixture->TestPoint(b2Vec2(x, y)); }

	//getters
	b2Body* getBody() { return _body; }
	b2Fixture* getFixture() { return _fixture; }
	const glm::vec2& getDimensions() const { return _dimensions; }
	glm::vec2 getPosition() const { return glm::vec2(_body->GetPosition().x, _body->GetPosition().y); }
	const BasicEngine::Color& getColor() const { return _color; }
	const BasicEngine::GLTexture& getTexture() const { return _texture; }
private:
	b2Body* _body = nullptr;
	b2Fixture* _fixture = nullptr;
	glm::vec2 _dimensions;
	glm::vec4 _uvRect;
	BasicEngine::Color _color;
	BasicEngine::GLTexture _texture;

};

