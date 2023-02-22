#include "InputManager.h"

namespace BasicEngine
{
	InputManager::InputManager() :_mouseCoords(0.0f, 0.0f)
	{

	}
	InputManager::~InputManager()
	{

	}

	void InputManager::update()
	{
		//Loop through _keymap and copy it over to _previousFrameKeyMap
		for (auto it = _keyMap.begin(); it != _keyMap.end(); it++)
		{
			_previousFrameKeyMap[it->first] = it->second;
		}
	}

	void InputManager::pressKey(unsigned int keyID)
	{
		_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID)
	{
		_keyMap[keyID] = false;
	}

	void InputManager::setMouseCoords(float x, float y)
	{
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}

	bool InputManager::isKeyDown(unsigned int keyID)
	{
		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end())
			return it->second;
		else
			return false;
	}

	bool InputManager::wasKeyDown(unsigned int keyID)
	{
		auto it = _previousFrameKeyMap.find(keyID);
		if (it != _previousFrameKeyMap.end())
			return it->second;
		else
			return false;
	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		//Check if the key is pressed this frame and wasnt pressed last frame
		return (isKeyDown(keyID) && !wasKeyDown(keyID));
	}
}
