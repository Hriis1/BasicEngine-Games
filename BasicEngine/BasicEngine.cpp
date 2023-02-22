#include <SDL/SDL.h>
#include <GL/glew.h>

#include "BasicEngine.h"

namespace BasicEngine {
	int init()
	{
		//Init SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//Tell SDL we want a double buffered window so we dont get any flickering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		return 0;
	}
}