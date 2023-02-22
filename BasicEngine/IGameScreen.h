#pragma once
#include "IMainGame.h"

#define SCREEN_INDEX_NO_SCREEN -1

namespace BasicEngine {

	enum class ScreenState
	{
		NONE,
		RUNNING,
		EXIT_APPLICATION,
		CHANGE_NEXT,
		CHENG_PREVIOUS
	};

	class IGameScreen
	{
		friend class ScreenList;
	private:

	protected:
		int _screenIndex = -1;
		ScreenState _currentState = ScreenState::NONE;
		IMainGame* _game = nullptr;
	public:
		IGameScreen() {}
		virtual ~IGameScreen() {}

		//Returns the index of next or prev scren when changing screens
		virtual int getNextScreenIndex() const = 0;
		virtual int getPreviousScreenIndex() const = 0;

		//Called at beggining and end of application
		virtual void build() = 0;
		virtual void destroy() = 0;

		//Called when a screen enters and exits focus
		virtual void onEntry() = 0;
		virtual void onExit() = 0;

		//Called in the main game loop
		virtual void update() = 0;
		virtual void draw() = 0;

		//getters
		int getScreenIndex() const { return _screenIndex; }
		ScreenState getState() const { return _currentState; }

		//setters
		void setParentGame(IMainGame* game) { _game = game; }
		void setRunning() { _currentState = ScreenState::RUNNING; }
	};
}

