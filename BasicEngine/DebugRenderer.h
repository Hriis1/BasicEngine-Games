#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"
#include "GLSLProgram.h"



namespace BasicEngine {

	class DebugRenderer
	{
	public:
		DebugRenderer();
		~DebugRenderer();

		void init();
		void end();
		void drawLine(const glm::vec2& a, const glm::vec2& b, const Color& color);
		void drawBox(const glm::vec4& destRect, const Color& color, float angle);
		void drawCircle(const glm::vec2& center, const Color& color, float radius);
		void render(const glm::mat4& projectionMatrix, float lineWidth);
		void dispose();

		struct DebugVertex
		{
			glm::vec2 position;
			Color color;
		};
	private:
		GLSLProgram _program;
		std::vector<DebugVertex> _verts;
		std::vector<GLuint> _indices;
		GLuint _vbo = 0, _vao = 0, _ibo = 0;
		int _numElements = 0;
	};

}
