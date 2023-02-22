#include "Errors.h"

#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>

namespace BasicEngine {
	//Prints out an error message and exits the game
	void fatalError(const std::string& errorString)
	{
		std::cout << errorString << std::endl;
		std::cin.get();
		SDL_Quit();
		exit(10);
	}
}