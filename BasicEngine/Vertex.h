#pragma once

#include <GL/glew.h>
namespace BasicEngine {
	struct Position
	{
		float x;
		float y;
	};

	struct Color
	{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;

		Color(): r(0), g(0), b(0), a(255){
		}

		Color(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a): r(_r), g(_g), b(_b), a(_a) {
		}
	};

	struct UV
	{
		float u;
		float v;
	};

	struct Vertex
	{
		Position position;

		Color color;

		//UV texture coordinates
		UV uv;

		void setPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}
	};
}