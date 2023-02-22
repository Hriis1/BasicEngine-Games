#include "MainMenuScreeen.h"

MainMenuScreeen::MainMenuScreeen(BasicEngine::Window* window)
	: _window(window)
{
	_screenIndex = SCREEN_INDEX_MAINMENU;
}

MainMenuScreeen::~MainMenuScreeen()
{
}

void MainMenuScreeen::initUI()
{
	_gui.init("GUI");
	_gui.loadScheme("TaharezLook.scheme");
	_gui.setFont("DejaVuSans-10");

	CEGUI::PushButton* playButton = static_cast<CEGUI::PushButton*>(_gui.createWidget("TaharezLook/Button", glm::vec4(0.45f, 0.5f, 0.1f, 0.05f), glm::vec4(0), "playButton"));
	playButton->setText("Play");
	playButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuScreeen::onPlayButtonClicked, this));

	CEGUI::PushButton* editorButton = static_cast<CEGUI::PushButton*>(_gui.createWidget("TaharezLook/Button", glm::vec4(0.45f, 0.6f, 0.1f, 0.05f), glm::vec4(0), "editorButton"));
	editorButton->setText("Level Editor");
	editorButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuScreeen::onEdditorButtonClicked, this));

	CEGUI::PushButton* exitButton = static_cast<CEGUI::PushButton*>(_gui.createWidget("TaharezLook/Button", glm::vec4(0.45f, 0.7f, 0.1f, 0.05f), glm::vec4(0), "exitButton"));
	exitButton->setText("Exit Game");
	//Set the onExitClicked event to be called when we click the exitButton
	exitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuScreeen::onExitClicked, this));


	//Curror stuff that doesn't work
	{
		//_gui.setMouseCursor("TaharezLook/VerticalScrollbarThumb");
		_gui.showMouseCursor();
		//SDL_ShowCursor(0);
	}
}

int MainMenuScreeen::getNextScreenIndex() const
{
	return _nextScreenIdx;
}

int MainMenuScreeen::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void MainMenuScreeen::build()
{
}

void MainMenuScreeen::destroy()
{
}

void MainMenuScreeen::onEntry()
{
	//Init the UI
	initUI();

	//Init camera
	_camera.init(_window->getScreenWidth(), _window->getScreenHeight());
	_camera.setScale(32.0f);
}

void MainMenuScreeen::onExit()
{
	_gui.destroy();
}

void MainMenuScreeen::update()
{
	//Update the camera
	_camera.update();

	// check for player input
	checkInput();
}

void MainMenuScreeen::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	//Draw the UI
	_gui.draw();
	glEnable(GL_BLEND);
}

void MainMenuScreeen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		_game->onSDLEvent(evnt);
		_gui.onSDLEvent(evnt);
	}
}

bool MainMenuScreeen::onPlayButtonClicked(const CEGUI::EventArgs& e)
{
	_nextScreenIdx = SCREEN_INDEX_GAMEPLAY;
	_currentState = BasicEngine::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreeen::onEdditorButtonClicked(const CEGUI::EventArgs& e)
{
	_nextScreenIdx = SCREEN_INDEX_EDITOR;
	_currentState = BasicEngine::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreeen::onExitClicked(const CEGUI::EventArgs& e)
{
	_currentState = BasicEngine::ScreenState::EXIT_APPLICATION;

	return true;
}
