#include "MainGame.h"
#include "Errors.h"

#include <ResourceManager.h>


MainGame::MainGame()
	:_screenWidth(1024),_screenHeight(768), _gameState(GameState::PLAY), _time(0.0f), _MAX_FPS(120.0f)
{
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{

}

void MainGame::Run()
{
	initSystems();

	

	gameLoop();
}

void MainGame::initSystems()
{
	BasicEngine::init();

	_window.createWindow("Game Engine", _screenWidth, _screenHeight, 0);

	initShaders();

	_spriteBatch.init();

	_fpsLimiter.init(_MAX_FPS);
}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("Shaders/colorShadingvert.txt", "Shaders/colorShadingfrag.txt");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop()
{
	//Will loop until we set _gameState to EXIT
	while (_gameState != GameState::EXIT)
	{
		_fpsLimiter.begin();

		processInput();
		_time += 0.01f;

		_camera.update();

		//Update all bullets
		for (size_t i = 0; i < _bullets.size();)
		{
			if (_bullets[i].update())
			{
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else
			{
				i++;
			}
		}
		drawGame();

		_fps = _fpsLimiter.end();

		//Print once every 10 frames
		static int currentFrame = 0;
		currentFrame++;
		if (currentFrame % 1000 == 0)
			std::cout << _fps << std::endl;

		if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
		{
			glm::vec2 mouseCoords = _inputManager.getMouseCoords();
			mouseCoords = _camera.convertScreenToWorld(mouseCoords);

			glm::vec2 playerPosition(0.0f);
			glm::vec2 direction = mouseCoords - playerPosition;
			direction = glm::normalize(direction);
			_bullets.emplace_back(playerPosition, direction, 2.0f, 1000);
			//std::cout << mouseCoords.x << " " << mouseCoords.y << std::endl;
		}
	}
}

void MainGame::processInput()
{
	SDL_Event e;
	const float CAMERA_SPEED = 2.0f;
	const float CAMERA_SCALE_SPEED = 0.01f;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
				break;
		case SDL_MOUSEMOTION:
			//std::cout << e.motion.x << " " << e.motion.y << std::endl;
			_inputManager.setMouseCoords(e.motion.x, e.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(e.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(e.key.keysym.sym);
			break;	
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(e.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(e.button.button);
			break;
		}
	}
	
	if(_inputManager.isKeyPressed(SDLK_w))
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -1.0 * CAMERA_SPEED));
	if (_inputManager.isKeyPressed(SDLK_s))
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, 1.0 * CAMERA_SPEED));
	if (_inputManager.isKeyPressed(SDLK_a))
		_camera.setPosition(_camera.getPosition() + glm::vec2(1.0 * CAMERA_SPEED, 0.0));
	if (_inputManager.isKeyPressed(SDLK_d))
		_camera.setPosition(_camera.getPosition() + glm::vec2(-1.0 * CAMERA_SPEED, 0.0));
	if (_inputManager.isKeyPressed(SDLK_q))
		_camera.setScale(_camera.getScale() + CAMERA_SCALE_SPEED);
	if (_inputManager.isKeyPressed(SDLK_e))
		_camera.setScale(_camera.getScale() - CAMERA_SCALE_SPEED);
}

void MainGame::drawGame()
{
	//Clear the screen
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	//Make it so that we use the fist bound texture
	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	//GLuint timeLocation = _colorProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, _time);

	GLuint orthoMatrixLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(orthoMatrixLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static BasicEngine::GLTexture texture = BasicEngine::ResourceManager::getTexture("Textures/JimmyJumpPack/PNG/CharacterRight_Standing.png");
	BasicEngine::Color color = { 255, 255,255,255 };

	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);

	for (size_t i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_spriteBatch);
	}
	
	_spriteBatch.end();

	_spriteBatch.renderBatch();

	//Unbind the player texture
	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unuse();

	//Swaps which window is being cleared and which window is being drawn
	_window.swapBuffer();
}