#pragma once

#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Vertex.h"

namespace BasicEngine
{
	
	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	class Glyph
	{
	public:
		GLuint texture;
		
		float depth;

		Vertex topLeft;
		Vertex botLeft;
		Vertex topRight;
		Vertex botRight;

	public:
		Glyph() {}
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint _texture, float _depth, const Color& color);
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint _texture, float _depth, const Color& color, float angle);

	private:
		glm::vec2 rotatePoint(const glm::vec2& pos, float angle);

	};

	struct RenderBatch
	{
		RenderBatch(GLuint _offset, GLuint _numVertecies, GLuint _texture)
			: offset(_offset), numVertecies(_numVertecies), texture(_texture)
		{

		}

		GLuint offset;
		GLuint numVertecies;
		GLuint texture;
	};

	class SpriteBatch
	{
	private:
		GLuint _vbo;
		GLuint _vao;

		GlyphSortType _sortType;

		std::vector<Glyph*> _glyphPointers; //This is for sorting
		std::vector<Glyph> _glyphs; //These are the actual glyphs
		std::vector<RenderBatch> _renderBtches;

	private:
		void createRenderBatches();

		void createVertexArray();

		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

	public:
		SpriteBatch();
		~SpriteBatch();

		void init();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, float angle);
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color,const glm::vec2& dir);
		void dispose();

		void renderBatch();
	};
}

