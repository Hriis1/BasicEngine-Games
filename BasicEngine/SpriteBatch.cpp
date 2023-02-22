#include "SpriteBatch.h"

namespace BasicEngine
{
	//------------------Glyph-----------------------------
	//------------------Glyph-----------------------------
	Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint _texture, float _depth, const Color& color)
		:texture(_texture), depth(_depth)
	{
		topLeft.setColor(color.r, color.g, color.b, color.a);
		topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		botLeft.setColor(color.r, color.g, color.b, color.a);
		botLeft.setPosition(destRect.x, destRect.y);
		botLeft.setUV(uvRect.x, uvRect.y);

		botRight.setColor(color.r, color.g, color.b, color.a);
		botRight.setPosition(destRect.x + destRect.z, destRect.y);
		botRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.setColor(color.r, color.g, color.b, color.a);
		topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}

	Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint _texture, float _depth, const Color& color, float angle)
		:texture(_texture), depth(_depth)
	{
		//Apply rotation
		//Get the positions of the top left, top right, bot left and bot right points of the sprite centered at x=0, y=0
		glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);
		glm::vec2 tl(-halfDims.x, halfDims.y);
		glm::vec2 tr(halfDims.x, halfDims.y);
		glm::vec2 bl(-halfDims.x, -halfDims.y);
		glm::vec2 br(halfDims.x, -halfDims.y);
		
		//Rotate the points, we add back halfDims to get the origin of the sprite back at the top-left
		tl = rotatePoint(tl, angle) + halfDims;
		tr = rotatePoint(tr, angle) + halfDims;
		bl = rotatePoint(bl, angle) + halfDims;
		br = rotatePoint(br, angle) + halfDims;

		topLeft.setColor(color.r, color.g, color.b, color.a);
		topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		botLeft.setColor(color.r, color.g, color.b, color.a);
		botLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
		botLeft.setUV(uvRect.x, uvRect.y);

		botRight.setColor(color.r, color.g, color.b, color.a);
		botRight.setPosition(destRect.x + br.x, destRect.y + br.y);
		botRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.setColor(color.r, color.g, color.b, color.a);
		topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}

	glm::vec2 Glyph::rotatePoint(const glm::vec2& pos, float angle)
	{
		glm::vec2 newPos;
		newPos.x = pos.x * cos(angle) - pos.y * sin(angle);
		newPos.y = pos.x * sin(angle) + pos.y * cos(angle);
		return newPos;
	}

	//------------------SpriteBatch-----------------------------
	//------------------SpriteBatch-----------------------------
	SpriteBatch::SpriteBatch()
		:_vbo(0), _vao(0)
	{

	}
	SpriteBatch::~SpriteBatch()
	{

	}

	void SpriteBatch::init()
	{
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType)
	{
		_sortType = sortType;

		_renderBtches.clear();

		_glyphs.clear();
	}
	void SpriteBatch::end()
	{
		//Make the _glyphPointers point to the coresponding glyphs in _glyphs
		_glyphPointers.resize(_glyphs.size());
		for (size_t i = 0; i < _glyphs.size(); i++)
		{
			_glyphPointers[i] = &_glyphs[i];
		}

		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::dispose() {
		if (_vao != 0) {
			glDeleteVertexArrays(1, &_vao);
			_vao = 0;
		}
		if (_vbo != 0) {
			glDeleteBuffers(1, &_vbo);
			_vbo = 0;
		}
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture,float depth, const Color& color)
	{
		_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
	}
	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, float angle)
	{
		_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
	}
	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, const glm::vec2& dir)
	{
		const glm::vec2 right(1.0f, 0.0f);
		float angle = acos(glm::dot(right, dir));
		if (dir.y < 0.0f)
			angle = -angle;

		_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
	}

	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(_vao);

		for (size_t i = 0; i < _renderBtches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, _renderBtches[i].texture);

			glDrawArrays(GL_TRIANGLES, _renderBtches[i].offset, _renderBtches[i].numVertecies);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertecies;
		vertecies.resize(_glyphPointers.size() * 6);

		if (_glyphPointers.empty())
			return;

		int offset = 0;
		int cv = 0; //current vertex
		_renderBtches.emplace_back(offset, 6, _glyphPointers[0]->texture);

		vertecies[cv++] = _glyphPointers[0]->topLeft;
		vertecies[cv++] = _glyphPointers[0]->botLeft;
		vertecies[cv++] = _glyphPointers[0]->botRight;
		vertecies[cv++] = _glyphPointers[0]->botRight;
		vertecies[cv++] = _glyphPointers[0]->topRight;
		vertecies[cv++] = _glyphPointers[0]->topLeft;
		offset += 6;

		int cg = 1; //current Glyph
		for (; cg < _glyphPointers.size(); cg++)
		{
			if(_glyphPointers[cg]->texture != _glyphPointers[cg-1]->texture)
				_renderBtches.emplace_back(offset, 6, _glyphPointers[cg]->texture);
			else
				_renderBtches.back().numVertecies += 6;

			vertecies[cv++] = _glyphPointers[cg]->topLeft;
			vertecies[cv++] = _glyphPointers[cg]->botLeft;
			vertecies[cv++] = _glyphPointers[cg]->botRight;
			vertecies[cv++] = _glyphPointers[cg]->botRight;
			vertecies[cv++] = _glyphPointers[cg]->topRight;
			vertecies[cv++] = _glyphPointers[cg]->topLeft;
			offset += 6;
		}

		//bind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		//orphan the data
		glBufferData(GL_ARRAY_BUFFER, vertecies.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		//upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertecies.size() * sizeof(Vertex), &(vertecies[0]));

		//unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	}

	void SpriteBatch::createVertexArray()
	{
		
		//Generate the vao
		if(_vao == 0)
			glGenVertexArrays(1, &_vao);

		//Bind the vao
		glBindVertexArray(_vao);

		//Generate the vbo
		if(_vbo == 0)
			glGenBuffers(1, &_vbo);

		//Bind the vbo
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		//Tell openGL we want to use the first attribute array. We only need 1 array for the position
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		//This is the color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		//This is the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//Unbind the vao
		glBindVertexArray(0);
	}

	void SpriteBatch::sortGlyphs()
	{
		switch (_sortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(),compareBackToFront);
			break;

		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareFrontToBack);
			break;

		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
			break;
		}
		
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return a->depth < b->depth;
	}
	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
	{
		return a->depth > b->depth;
	}
	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
	{
		return a->texture < b->texture;
	}
}