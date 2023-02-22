#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace BasicEngine
{
	class InputManager
	{
	private:
		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _previousFrameKeyMap;
		glm::vec2 _mouseCoords;

	private:
		//Returns true if the key was held down in the prev frame
		bool wasKeyDown(unsigned int keyID);

	public:
		InputManager();
		~InputManager();

		void update();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		void setMouseCoords(float x, float y);

		//Returns true if the key is held down
		bool isKeyDown(unsigned int keyID);

		//Returns true if the key has just been pressed
		bool isKeyPressed(unsigned int keyID);


		//getters
		glm::vec2 getMouseCoords() const { return _mouseCoords; }
	};
}

