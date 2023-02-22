#pragma once
#include <vector>

namespace BasicEngine {

	class IMainGame;
	class IGameScreen;

	class ScreenList
	{
	private:

	protected:
		IMainGame* _game = nullptr;
		std::vector<IGameScreen*> _screens;
		int _currentScreenIndex = -1;
	public:
		ScreenList(IMainGame* game);
		~ScreenList();

		IGameScreen* moveNext();
		IGameScreen* movePrevious();

		void setScreen(int nextScreen);
		void addScreen(IGameScreen* newScreen);

		void destroy();

		//getters
		IGameScreen* getCurrent();

	};
}
