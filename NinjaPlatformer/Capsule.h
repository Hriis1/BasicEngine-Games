#pragma once
#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <DebugRenderer.h>

class Capsule
{
public:

	void init(b2World* world, const glm::vec2& pos, const glm::vec2& dimensions, float density,float friction, bool fixedRotation);
	void destroy(b2World* world);

	void drawDebug(BasicEngine::DebugRenderer& debugRenderer);

	//getters
	b2Body* getBody() const { return _body; }
	b2Fixture* getFixture(int idx) const { return _fixtures[idx]; }
	const glm::vec2& getDimensions() const { return _dimensions; }
private:
	b2Body* _body = nullptr;
	b2Fixture* _fixtures[3];
	glm::vec2 _dimensions;
	glm::vec4 _uvRect;

};

