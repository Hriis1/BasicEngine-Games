#include "GameplayScreen.h"
#include <iostream>
#include <SDL/SDL.h>
#include <IMainGame.h>
#include <ResourceManager.h>
#include <random>

#include"Lighting.h"
#include "ScreenIndices.h"


GameplayScreen::GameplayScreen(BasicEngine::Window* window)
{
	_window = window;
	_screenIndex = SCREEN_INDEX_GAMEPLAY;
}

GameplayScreen::~GameplayScreen()
{
}

void GameplayScreen::initShaders()
{
	//Compile texture shader
	_textureProgram.compileShaders("Shaders/colorShadingvert.txt", "Shaders/colorShadingfrag.txt");
	_textureProgram.addAttribute("vertexPosition");
	_textureProgram.addAttribute("vertexColor");
	_textureProgram.addAttribute("vertexUV");
	_textureProgram.linkShaders();

	//Compile light shader
	_lightProgram.compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
	_lightProgram.addAttribute("vertexPosition");
	_lightProgram.addAttribute("vertexColor");
	_lightProgram.addAttribute("vertexUV");
	_lightProgram.linkShaders();
}

void GameplayScreen::initUI()
{
	_gui.init("GUI");
	_gui.loadScheme("TaharezLook.scheme");
	_gui.setFont("DejaVuSans-10");
	CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(_gui.createWidget("TaharezLook/Button", glm::vec4(0.9f, 0.0f, 0.1f, 0.05f), glm::vec4(0), "testButton"));
	testButton->setText("Exit Game");

	//Set the onExitClicked event to be called when we click the testbutton
	testButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameplayScreen::onExitClicked, this));

	CEGUI::Combobox* testComboBox = static_cast<CEGUI::Combobox*>(_gui.createWidget("TaharezLook/Combobox", glm::vec4(0.2f, 0.2f, 0.1f, 0.05f), glm::vec4(0), "testComboBox"));

	//_gui.setMouseCursor("TaharezLook/VerticalScrollbarThumb");
	_gui.showMouseCursor();
	//SDL_ShowCursor(0);
}

int GameplayScreen::getNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_MAINMENU;
}

void GameplayScreen::build()
{
}

void GameplayScreen::destroy()
{
}

void GameplayScreen::onEntry()
{
	//Init physics world
	b2Vec2 gravity(0.0f, -40.0f);
	_world = std::make_unique<b2World>(gravity);

	//Init the debug renderer
	_debugRenderer.init();

	//Make the ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f,-20.0f);
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);
	//Make the ground fixture
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox,0.0f);

	//Load the brick texture
	_texture = BasicEngine::ResourceManager::getTexture("Assets/bricks_top.png");

	//Make a bunch of boxes
	std::mt19937 randGenerator;
	std::uniform_real_distribution<float> xPos(-10.0f, 10.0f);
	std::uniform_real_distribution<float> yPos(-10.0f, 20.0f);
	std::uniform_real_distribution<float> size(0.5f, 2.5f);
	const int NUM_BOXES = 15;
	for (size_t i = 0; i < NUM_BOXES; i++)
	{
		std::uniform_int_distribution<int> colorDist(0,255);
		BasicEngine::Color randColor(colorDist(randGenerator), colorDist(randGenerator), colorDist(randGenerator), 255);
		_boxes.emplace_back();
		float sz = size(randGenerator);
		_boxes.back().init(_world.get(), glm::vec2(xPos(randGenerator), yPos(randGenerator)), glm::vec2(size(randGenerator), size(randGenerator)),_texture,randColor, false,true);
	}
	
	//Init spriteBatch
	_spriteBatch.init();

	//Init shaders
	initShaders();

	//Init camera
	_camera.init(_window->getScreenWidth(), _window->getScreenHeight());
	_camera.setScale(32.0f);

	//Init player
	_player.init(_world.get(), glm::vec2(0.0f, 30.0f), glm::vec2(2.0f), glm::vec2(1.0f, 1.8f), BasicEngine::Color(255,255,255,255));

	//Init the UI
	initUI();
}

void GameplayScreen::onExit()
{
	_debugRenderer.dispose();

	_gui.destroy();

	_textureProgram.dispose();
	_lightProgram.dispose();
}

void GameplayScreen::update()
{
	//Update the camera
	_camera.update();

	//check for player input
	checkInput();

	//Update the player
	_player.update(_game->inputManager);

	//Update the physics symulation
	_world->Step(1.0f / 60.0f, 6, 2);
}

void GameplayScreen::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	_textureProgram.use();

	//Upload texture uniform
	GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	//Upload camera matrix
	glm::mat4 projectionMatrix = _camera.getCameraMatrix();
	GLint pUniform = _textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	_spriteBatch.begin();

	//Draw all the boxes
	for (auto& b : _boxes)
	{
		b.draw(_spriteBatch);
	}

	//Draw the player
	_player.draw(_spriteBatch);

	_spriteBatch.end();

	_spriteBatch.renderBatch();

	_textureProgram.unuse();

	//Debug rendering
	if (_renderDebug)
	{
		//Draw boxes
		glm::vec4 destRect;
		for (auto& b : _boxes) {
			destRect.x = b.getBody()->GetPosition().x - b.getDimensions().x / 2.0f;
			destRect.y = b.getBody()->GetPosition().y - b.getDimensions().y / 2.0f;
			destRect.z = b.getDimensions().x;
			destRect.w = b.getDimensions().y;
			_debugRenderer.drawBox(destRect, BasicEngine::Color(255, 255, 255, 255), b.getBody()->GetAngle());
		}

		//Draw player
		_player.drawDebug(_debugRenderer);

		_debugRenderer.end();
		_debugRenderer.render(projectionMatrix, 2.0f);
	}

	//Render some lights
	BasicLight playerLight;
	playerLight.color = BasicEngine::Color(255, 155, 155, 150);
	playerLight.position = _player.getPosition();
	playerLight.size = 30.0f;

	BasicLight mouseLight;
	mouseLight.color = BasicEngine::Color(255, 0, 155, 80);
	mouseLight.position = _camera.convertScreenToWorld(_game->inputManager.getMouseCoords());
	mouseLight.size = 30.0f;

	_lightProgram.use();

	pUniform = _lightProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	//Additive blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	_spriteBatch.begin();

	playerLight.draw(_spriteBatch);
	mouseLight.draw(_spriteBatch);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	_lightProgram.unuse();

	//Reset to regular alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Draw the UI
	_gui.draw();
	glEnable(GL_BLEND);
}

void GameplayScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		_game->onSDLEvent(evnt);
		_gui.onSDLEvent(evnt);
	}

	if (_game->inputManager.isKeyPressed(SDLK_1))
		_renderDebug = !_renderDebug;
}

bool GameplayScreen::onExitClicked(const CEGUI::EventArgs& e)
{
	_currentState = BasicEngine::ScreenState::EXIT_APPLICATION;

	return true;
}
