#include "EditorScreen.h"

#include <ResourceManager.h>
#include <iostream>

const float smaallLightCircleSize = 0.5f;

EditorScreen::EditorScreen(BasicEngine::Window* window)
	: _window(window), _boxDims(1.0f)
{
	_screenIndex = SCREEN_INDEX_EDITOR;
}

EditorScreen::~EditorScreen()
{
	
}

void EditorScreen::initUI()
{
	_gui.init("GUI");
	_gui.loadScheme("TaharezLook.scheme");
	_gui.setFont("DejaVuSans-10");

	//Group box
	_groupBox = _gui.createWidget(("TaharezLook/GroupBox"), glm::vec4(0.01f, 0.01f, 0.25f, 0.9f), glm::vec4(0), "groupBox");

	//Slider for red value
	_rSlider = static_cast<CEGUI::Slider*>(_gui.createWidget(_groupBox, ("TaharezLook/Slider"), glm::vec4(0.05f, 0.05f, 0.05f, 0.15f), glm::vec4(0), "rSlider"));
	_rSlider->setMaxValue(255.0f);
	_rSlider->setCurrentValue(_colorPickerRed);
	_rSlider->setClickStep(1.0f);
	_rSlider->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&EditorScreen::onColorPickerRedChanged, this));

	//Slider for green value
	_gSlider = static_cast<CEGUI::Slider*>(_gui.createWidget(_groupBox, ("TaharezLook/Slider"), glm::vec4(0.11f, 0.05f, 0.05f, 0.15f), glm::vec4(0), "gSlider"));
	_gSlider->setMaxValue(255.0f);
	_gSlider->setCurrentValue(_colorPickerGreen);
	_gSlider->setClickStep(1.0f);
	_gSlider->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&EditorScreen::onColorPickerGreenChanged, this));

	//Slider for blue value
	_bSlider = static_cast<CEGUI::Slider*>(_gui.createWidget(_groupBox, ("TaharezLook/Slider"), glm::vec4(0.17f, 0.05f, 0.05f, 0.15f), glm::vec4(0), "bSlider"));
	_bSlider->setMaxValue(255.0f);
	_bSlider->setCurrentValue(_colorPickerBlue);
	_bSlider->setClickStep(1.0f);
	_bSlider->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&EditorScreen::onColorPickerBlueChanged, this));

	//Exit button
	CEGUI::PushButton* exitButton = static_cast<CEGUI::PushButton*>(_gui.createWidget(_groupBox, "TaharezLook/Button", glm::vec4(0.25f, 0.9f, 0.5f, 0.075f), glm::vec4(0), "exitButton"));
	exitButton->setText("Back");
	//Set the onExitClicked event to be called when we click the exitButton
	exitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&EditorScreen::onBackClicked, this));

	{//Add objectmode radio buttons
		const int GROUP_ID = 1;
		_playerRadioButton = static_cast<CEGUI::RadioButton*>(_gui.createWidget(_groupBox, "TaharezLook/RadioButton", glm::vec4(0.05f, 0.3f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 20.0f, 20.0f), "playerRadioButton"));
		_playerRadioButton->subscribeEvent(CEGUI::RadioButton::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::onPlayerButtonClicked, this));
		_playerRadioButton->setSelected(false);
		createLableForUIElement(_playerRadioButton, "Player");
		_playerRadioButton->setGroupID(GROUP_ID);

		_platformRadioButton = static_cast<CEGUI::RadioButton*>(_gui.createWidget(_groupBox, "TaharezLook/RadioButton", glm::vec4(0.3f, 0.3f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 20.0f, 20.0f), "platfromRadioButton"));
		_platformRadioButton->subscribeEvent(CEGUI::RadioButton::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::onPlatformButtonClicked, this));
		_platformRadioButton->setSelected(true);
		createLableForUIElement(_platformRadioButton, "Platform");
		_platformRadioButton->setGroupID(GROUP_ID);

		_lightRadioButton = static_cast<CEGUI::RadioButton*>(_gui.createWidget(_groupBox, "TaharezLook/RadioButton", glm::vec4(0.55f, 0.3f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 20.0f, 20.0f), "lightRadioButton"));
		_lightRadioButton->subscribeEvent(CEGUI::RadioButton::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::onLightButtonClicked, this));
		_lightRadioButton->setSelected(false);
		createLableForUIElement(_lightRadioButton, "Light");
		_lightRadioButton->setGroupID(GROUP_ID);

	}

	{//Add physics mode radio buttons
		const int GROUP_ID = 2;
		_rigidRadioButton = static_cast<CEGUI::RadioButton*>(_gui.createWidget(_groupBox, "TaharezLook/RadioButton", glm::vec4(0.05f, 0.4f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 20.0f, 20.0f), "rigidRadioButton"));
		_rigidRadioButton->setSelected(false);
		_rigidRadioButton->subscribeEvent(CEGUI::RadioButton::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::onRigidButtonClicked, this));
		createLableForUIElement(_rigidRadioButton, "Rigid");
		_rigidRadioButton->setGroupID(GROUP_ID);

		_dynamicRadioButton = static_cast<CEGUI::RadioButton*>(_gui.createWidget(_groupBox, "TaharezLook/RadioButton", glm::vec4(0.3f, 0.4f, 0.0f, 0.0f),
			glm::vec4(glm::vec4(0.0f, 0.0f, 20.0f, 20.0f)), "dynamicRadioButton"));
		_dynamicRadioButton->setSelected(true);
		_dynamicRadioButton->subscribeEvent(CEGUI::RadioButton::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::onDynamicButtonClicked, this));
		createLableForUIElement(_dynamicRadioButton, "Dynamic");
		_dynamicRadioButton->setGroupID(GROUP_ID);
	}

	{//Add selection mode radio buttons
		const int GROUP_ID = 3;
		_selectRadioButton = static_cast<CEGUI::RadioButton*>(_gui.createWidget(_groupBox, "TaharezLook/RadioButton", glm::vec4(0.05f, 0.8f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 20.0f, 20.0f), "selectRadioButton"));
		_selectRadioButton->setSelected(false);
		_selectRadioButton->subscribeEvent(CEGUI::RadioButton::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::onSelectButtonClicked, this));
		createLableForUIElement(_selectRadioButton, "Select");
		_selectRadioButton->setGroupID(GROUP_ID);

		_placeRadioButton = static_cast<CEGUI::RadioButton*>(_gui.createWidget(_groupBox, "TaharezLook/RadioButton", glm::vec4(0.3f, 0.8f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 20.0f, 20.0f), "placeRadioButton"));
		_placeRadioButton->setSelected(true);
		_placeRadioButton->subscribeEvent(CEGUI::RadioButton::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::onPlaceButtonClicked, this));
		createLableForUIElement(_placeRadioButton, "Place");
		_placeRadioButton->setGroupID(GROUP_ID);
	}

	//Add Debug toggle
	_debugToggle = static_cast<CEGUI::ToggleButton*>(_gui.createWidget(_groupBox, "TaharezLook/Checkbox", glm::vec4(0.8f, 0.8f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 20.0f, 20.0f), "debugToggle"));
	_debugToggle->subscribeEvent(CEGUI::RadioButton::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::onDebugToggleClicked, this));
	createLableForUIElement(_debugToggle, "Debug");

	{//Add platform dims and rotation spinners
		_widthSpinner = static_cast<CEGUI::Spinner*>(_gui.createWidget(_groupBox, "TaharezLook/Spinner", glm::vec4(0.15f, 0.55f, 0.2f, 0.05f),
			glm::vec4(0.0f), "widthSpinner"));
		_widthSpinner->setMinimumValue(0.0);
		_widthSpinner->setMaximumValue(10000.0);
		_widthSpinner->setCurrentValue(_boxDims.x);
		_widthSpinner->setStepSize(0.1);
		_widthSpinner->setTextInputMode(CEGUI::Spinner::FloatingPoint);
		_widthSpinner->subscribeEvent(CEGUI::Spinner::EventValueChanged, CEGUI::Event::Subscriber(&EditorScreen::onWidthValueChange, this));
		createLableForUIElement(_widthSpinner, "Width",0.06f);

		_heightSpinner = static_cast<CEGUI::Spinner*>(_gui.createWidget(_groupBox, "TaharezLook/Spinner", glm::vec4(0.65f, 0.55f, 0.2f, 0.05f),
			glm::vec4(0.0f), "heightSpinner"));
		_heightSpinner->setMinimumValue(0.0);
		_heightSpinner->setMaximumValue(10000.0);
		_heightSpinner->setCurrentValue(_boxDims.y);
		_heightSpinner->setStepSize(0.1);
		_heightSpinner->setTextInputMode(CEGUI::Spinner::FloatingPoint);
		_heightSpinner->subscribeEvent(CEGUI::Spinner::EventValueChanged, CEGUI::Event::Subscriber(&EditorScreen::onHeightValueChange, this));
		createLableForUIElement(_heightSpinner, "Height", 0.06f);

		_rotationSpinner = static_cast<CEGUI::Spinner*>(_gui.createWidget(_groupBox, "TaharezLook/Spinner", glm::vec4(0.65f, 0.4f, 0.2f, 0.05f),
			glm::vec4(0.0f), "rotationSpinner"));
		_rotationSpinner->setMinimumValue(-M_PI * 2.0);
		_rotationSpinner->setMaximumValue(M_PI * 2.0);
		_rotationSpinner->setCurrentValue(_boxRotation);
		_rotationSpinner->setStepSize(0.01);
		_rotationSpinner->setTextInputMode(CEGUI::Spinner::FloatingPoint);
		_rotationSpinner->subscribeEvent(CEGUI::Spinner::EventValueChanged, CEGUI::Event::Subscriber(&EditorScreen::onRotationValueChange, this));
		createLableForUIElement(_rotationSpinner, "Rotation", 0.06f);
	}

	{//Add the light intensity and size spinners
		_lightIntensitySpinner = static_cast<CEGUI::Spinner*>(_gui.createWidget(_groupBox, "TaharezLook/Spinner", glm::vec4(0.15f, 0.4f, 0.2f, 0.05f),
			glm::vec4(0.0f), "lightIntensitySpinner"));
		_lightIntensitySpinner->setMinimumValue(0);
		_lightIntensitySpinner->setMaximumValue(255);
		_lightIntensitySpinner->setCurrentValue(_lightIntensity);
		_lightIntensitySpinner->setStepSize(1);
		_lightIntensitySpinner->setTextInputMode(CEGUI::Spinner::Integer);
		_lightIntensitySpinner->subscribeEvent(CEGUI::Spinner::EventValueChanged, CEGUI::Event::Subscriber(&EditorScreen::onLightIntensityValueChange, this));
		createLableForUIElement(_lightIntensitySpinner, "Intensity", 0.06f);

		_lightSizeSpinner = static_cast<CEGUI::Spinner*>(_gui.createWidget(_groupBox, "TaharezLook/Spinner", glm::vec4(0.65f, 0.4f, 0.2f, 0.05f),
			glm::vec4(0.0f), "lightSizeSpinner"));
		_lightSizeSpinner->setMinimumValue(0.0f);
		_lightSizeSpinner->setMaximumValue(100.0f);
		_lightSizeSpinner->setCurrentValue(_lightSize);
		_lightSizeSpinner->setStepSize(0.1f);
		_lightSizeSpinner->setTextInputMode(CEGUI::Spinner::FloatingPoint);
		_lightSizeSpinner->subscribeEvent(CEGUI::Spinner::EventValueChanged, CEGUI::Event::Subscriber(&EditorScreen::onLightSizeValueChange, this));
		createLableForUIElement(_lightSizeSpinner, "Size", 0.06f);

		setLightWidgetsVisibility(false);
	}

	
	//Curror stuff that doesn't work
	{
		//_gui.setMouseCursor("TaharezLook/VerticalScrollbarThumb");
		_gui.showMouseCursor();
		//SDL_ShowCursor(0);
	}
}

void EditorScreen::initShaders()
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

int EditorScreen::getNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

int EditorScreen::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_MAINMENU;
}

void EditorScreen::build()
{
}

void EditorScreen::destroy()
{
}

void EditorScreen::onEntry()
{
	//Init the UI
	initUI();

	//Init physics world
	b2Vec2 gravity(0.0f, -40.0f);
	_world = std::make_unique<b2World>(gravity);

	//Init the debug renderer
	_debugRenderer.init();

	//Init UIcamera
	_UIcamera.init(_window->getScreenWidth(), _window->getScreenHeight());
	_UIcamera.setScale(1.0f);

	//Init main camera
	_mainCamera.init(_window->getScreenWidth(), _window->getScreenHeight());
	_mainCamera.setScale(32.0f);

	//Init the sprite batch
	_spriteBatch.init();

	//Init shaders
	initShaders();

	//Init blankTexture
	_blankTexture =  BasicEngine::ResourceManager::getTexture("Assets/blank.png").id;
}

void EditorScreen::onExit()
{
	_debugRenderer.dispose();

	_textureProgram.dispose();
	_lightProgram.dispose();
	_spriteBatch.dispose();

	resetWorld();
	resetUI();

	_world.reset();

	_gui.destroy();
}

void EditorScreen::resetWorld()
{

	_boxes.clear();
	_lights.clear();
	if (_player != nullptr)
	{
		_player->destroy(_world.get());
		delete _player;
		_player = nullptr;
	}
}

void EditorScreen::resetUI()
{
	_physicsMode = PhysicsMode::DYNAMIC;
	_objectMode = ObjectMode::PLATFORM;
	_selectionMode = SelectionMode::PLACE;
}


void EditorScreen::update()
{
	//Update the camera
	_UIcamera.update();

	//Update the main camera
	_mainCamera.update();

	// check for player input
	checkInput();

}

void EditorScreen::updateSelectedBox()
{
	if (_selectionMode == SelectionMode::SELECT)
	{
		if(_objectMode == ObjectMode::PLATFORM)
		{
			if (_selectedBoxIdx != -1)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				glm::vec2 pos = _mainCamera.convertScreenToWorld(glm::vec2(x, y));
				refreshSelectedBox(pos);
			}
		}
	}
}

void EditorScreen::updateSelectedLight()
{
	if (_selectionMode == SelectionMode::SELECT)
	{
		if (_objectMode == ObjectMode::LIGHT)
		{
			if (_selectedLightIdx != -1)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				glm::vec2 pos = _mainCamera.convertScreenToWorld(glm::vec2(x, y));
				_lights[_selectedLightIdx].position = pos;
				_lights[_selectedLightIdx].size = _lightSize;
				_lights[_selectedLightIdx].color = BasicEngine::Color(_colorPickerRed, _colorPickerGreen, _colorPickerBlue, _lightIntensity);
			}
		}
	}
}

void EditorScreen::refreshSelectedBox(const glm::vec2& newPosition) {
	if (_selectedBoxIdx == -1) return;
	// Texture for boxes. Its here because lazy.
	static BasicEngine::GLTexture texture = BasicEngine::ResourceManager::getTexture("Assets/bricks_top.png");
	glm::vec4 uvRect;
	uvRect.x = newPosition.x;
	uvRect.y = newPosition.y;
	uvRect.z = _boxDims.x;
	uvRect.w = _boxDims.y;
	Box newBox;

	newBox.init(_world.get(), newPosition, _boxDims, texture, BasicEngine::Color((GLubyte)_colorPickerRed, (GLubyte)_colorPickerGreen, (GLubyte)_colorPickerBlue, 255),
		false, _physicsMode == PhysicsMode::DYNAMIC, _boxRotation, uvRect);
	// Destroy old box and replace with new one
	_boxes[_selectedBoxIdx].destroy(_world.get());
	_boxes[_selectedBoxIdx] = newBox;
}

void EditorScreen::deleteSelectedItem()
{
	if (_selectedBoxIdx != -1)
	{
		_boxes[_selectedBoxIdx].destroy(_world.get());
		_boxes[_selectedBoxIdx] = _boxes.back();
		_boxes.pop_back();
		_selectedBoxIdx = -1;
	}

	if (_selectedLightIdx != -1)
	{
		_lights[_selectedLightIdx] = _lights.back();
		_lights.pop_back();
		_selectedLightIdx = -1;
	}
}

void EditorScreen::drawUI()
{
	_textureProgram.use();

	//Upload UIcamera matrix
	glm::mat4 UIprojectionMatrix = _UIcamera.getCameraMatrix();
	GLint pUniform = _textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &UIprojectionMatrix[0][0]);



	{//Draw the color picker quad
		_spriteBatch.begin();

		const float COLOR_PICKER_DIMS = 50.0f;
		const float xOffset = 80.0f;
		const float yOffset = 80.0f;
		glm::vec4 destRect;
		destRect.x = (_bSlider->getXPosition().d_scale * _groupBox->getWidth().d_scale * _window->getScreenWidth()) + xOffset - _window->getScreenWidth() / 2.0f;
		destRect.y = _window->getScreenHeight() / 2.0f - (_bSlider->getYPosition().d_scale * _groupBox->getHeight().d_scale * _window->getScreenHeight()) - yOffset;
		destRect.z = COLOR_PICKER_DIMS;
		destRect.w = COLOR_PICKER_DIMS;
		_spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _blankTexture, 0.0f, BasicEngine::Color((GLubyte)_colorPickerRed, (GLubyte)_colorPickerGreen, (GLubyte)_colorPickerBlue, 255.0f));

		_spriteBatch.end();
	}
	_spriteBatch.renderBatch();

	_textureProgram.unuse();

	//Draw the UI
	_gui.draw();
	glEnable(GL_BLEND);
}

void EditorScreen::drawWorld()
{
	_textureProgram.use();

	//Upload texture uniform
	GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	glm::mat4 projectionMatrix = _mainCamera.getCameraMatrix();
	GLint pUniform = _textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	_spriteBatch.begin();

	//Draw all the boxes
	for (auto& b : _boxes)
	{
		b.draw(_spriteBatch);
	}

	//Draw player
	if (_player != nullptr)
		_player->draw(_spriteBatch);

	_spriteBatch.end();

	_spriteBatch.renderBatch();

	_textureProgram.unuse();

	
	//Draw lights
	_lightProgram.use();

	pUniform = _lightProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	//Additive blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	_spriteBatch.begin();

	for (auto& l : _lights)
	{
		l.draw(_spriteBatch);
	}

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	_lightProgram.unuse();

	//Reset to regular alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Debug rendering
	if (_debugRender)
	{
		//Draw the horizontal and the vertical axis lines
		_debugRenderer.drawLine(glm::vec2(0, -10000), glm::vec2(0, 10000), BasicEngine::Color(255, 0, 0, 255));
		_debugRenderer.drawLine(glm::vec2(-10000, 0), glm::vec2(10000, 0), BasicEngine::Color(0, 255, 0, 255));

		//Draw the preview box
		//left line
		int x, y;
		SDL_GetMouseState(&x, &y);
		glm::vec2 pos = _mainCamera.convertScreenToWorld(glm::vec2(x, y));
		// Draw the object placement outlines
		if (!isMouseInUI())
		{
			if (_selectionMode == SelectionMode::SELECT)
			{

			}
			else //_selectionMode = SelectionMode::PLACE
			{
				if (_objectMode == ObjectMode::PLATFORM) {
					_debugRenderer.drawBox(glm::vec4(pos - _boxDims * 0.5f, _boxDims), BasicEngine::Color(255, 255, 255, 200), _boxRotation);
				}
				else if (_objectMode == ObjectMode::LIGHT) {
					_debugRenderer.drawCircle(pos, BasicEngine::Color(255, 255, 255, 200), _lightSize/2.0f);
					_debugRenderer.drawCircle(pos, BasicEngine::Color(255, 255, 255, 200), smaallLightCircleSize);
				}
			}
			
		}


		_debugRenderer.end();
		_debugRenderer.render(_mainCamera.getCameraMatrix(), 1.0f);
	}
}

void EditorScreen::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	drawWorld();
	drawUI();
}

void EditorScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		_game->onSDLEvent(evnt);
		_gui.onSDLEvent(evnt);

		switch (evnt.type) {
		case SDL_MOUSEBUTTONDOWN:
			updateMouseDown(evnt);
			break;
		case SDL_MOUSEBUTTONUP:
			updateMouseUp(evnt);
			break;
		case SDL_MOUSEMOTION:
			updateMouseMotion(evnt);
			break;
		case SDL_MOUSEWHEEL:
			// Linear scaling sucks for mouse wheel zoom so we multiply by getScale() instead.
			_mainCamera.offsetScale(_mainCamera.getScale() * evnt.wheel.y * 0.1f);
			break;
		}
	}

	updateObjectValues();
}

void EditorScreen::updateObjectValues()
{
	float valueAddAmount;
	if (_objectMode == ObjectMode::PLATFORM)
	{
		//Update box dims
		if (_game->inputManager.isKeyDown(SDLK_UP))
		{
			valueAddAmount = _heightSpinner->getStepSize() / 2.0f;
			_heightSpinner->setCurrentValue(_heightSpinner->getCurrentValue() + valueAddAmount);
		}
		else if (_game->inputManager.isKeyDown(SDLK_DOWN))
		{
			valueAddAmount = _heightSpinner->getStepSize() / 2.0f;
			_heightSpinner->setCurrentValue(_heightSpinner->getCurrentValue() - valueAddAmount);
		}
		if (_game->inputManager.isKeyDown(SDLK_LEFT))
		{
			valueAddAmount = _widthSpinner->getStepSize() / 2.0f;
			_widthSpinner->setCurrentValue(_widthSpinner->getCurrentValue() - valueAddAmount);
		}
		else if (_game->inputManager.isKeyDown(SDLK_RIGHT))
		{
			valueAddAmount = _widthSpinner->getStepSize() / 2.0f;
			_widthSpinner->setCurrentValue(_widthSpinner->getCurrentValue() + valueAddAmount);
		}

		//Update box rotation
		if (_game->inputManager.isKeyDown(SDLK_q))
		{
			valueAddAmount = _rotationSpinner->getStepSize();
			_rotationSpinner->setCurrentValue(_rotationSpinner->getCurrentValue() - valueAddAmount);
		}
		else if (_game->inputManager.isKeyDown(SDLK_e))
		{
			valueAddAmount = _rotationSpinner->getStepSize();
			_rotationSpinner->setCurrentValue(_rotationSpinner->getCurrentValue() + valueAddAmount);
		}
	}
	else if (_objectMode == ObjectMode::LIGHT)
	{
		//Update light Intensity and Size dims
		if (_game->inputManager.isKeyDown(SDLK_UP))
		{
			valueAddAmount = _lightSizeSpinner->getStepSize() / 2.0f;
			_lightSizeSpinner->setCurrentValue(_lightSizeSpinner->getCurrentValue() + valueAddAmount);
		}
		else if (_game->inputManager.isKeyDown(SDLK_DOWN))
		{
			valueAddAmount = _lightSizeSpinner->getStepSize() / 2.0f;
			_lightSizeSpinner->setCurrentValue(_lightSizeSpinner->getCurrentValue() - valueAddAmount);
		}
		if (_game->inputManager.isKeyDown(SDLK_LEFT))
		{
			valueAddAmount = _lightIntensitySpinner->getStepSize() / 2.0f;
			_lightIntensitySpinner->setCurrentValue(_lightIntensitySpinner->getCurrentValue() - valueAddAmount);
		}
		else if (_game->inputManager.isKeyDown(SDLK_RIGHT))
		{
			valueAddAmount = _lightIntensitySpinner->getStepSize() / 2.0f;
			_lightIntensitySpinner->setCurrentValue(_lightIntensitySpinner->getCurrentValue() + valueAddAmount);
		}
	}
}

void EditorScreen::setPlatformWidgetsVisibility(bool visible)
{
	_rigidRadioButton->setVisible(visible);
	_labelMap[_rigidRadioButton]->setVisible(visible);

	_dynamicRadioButton->setVisible(visible);
	_labelMap[_dynamicRadioButton]->setVisible(visible);

	_widthSpinner->setVisible(visible);
	_labelMap[_widthSpinner]->setVisible(visible);

	_heightSpinner->setVisible(visible);
	_labelMap[_heightSpinner]->setVisible(visible);

	_rotationSpinner->setVisible(visible);
	_labelMap[_rotationSpinner]->setVisible(visible);
}

void EditorScreen::setLightWidgetsVisibility(bool visible)
{
	_lightIntensitySpinner->setVisible(visible);
	_labelMap[_lightIntensitySpinner]->setVisible(visible);

	_lightSizeSpinner->setVisible(visible);
	_labelMap[_lightSizeSpinner]->setVisible(visible);
}

void EditorScreen::createLableForUIElement(CEGUI::Window* element, const std::string& text, float _xOffset, float _yOffset)
{
	const float xSize = 0.2f;
	const float ySize = 0.025f;

	const float xOffSet = -0.083 + _xOffset;
	const float yOffSet = -0.03 + _yOffset;

	glm::vec4 relPos;
	relPos.x = element->getXPosition().d_scale + xOffSet;
	relPos.y = element->getYPosition().d_scale + yOffSet;
	relPos.z = xSize;
	relPos.w = ySize;

	CEGUI::Window* newLabel = _gui.createWidget(element->getParent(), "TaharezLook/Label",relPos, glm::vec4(0));
	newLabel->setText(text);

	_labelMap[element] = newLabel;
}

bool EditorScreen::isMouseInUI() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	const float SW = (float)_window->getScreenWidth();
	const float SH = (float)_window->getScreenHeight();

	// Dont convert screen to world coz we are dealing with UI
	return (x >= _groupBox->getXPosition().d_scale * SW && x <= _groupBox->getXPosition().d_scale * SW + _groupBox->getWidth().d_scale * SW &&
		y >= _groupBox->getYPosition().d_scale * SH && y <= _groupBox->getYPosition().d_scale * SH + _groupBox->getHeight().d_scale * SH);
}

void EditorScreen::updateMouseDown(SDL_Event evnt)
{
	if (isMouseInUI()) return;

	static BasicEngine::GLTexture texture = BasicEngine::ResourceManager::getTexture("Assets/bricks_top.png");
	glm::vec2 pos;
	glm::vec4 uvRect;
	switch (evnt.button.button) {
	case SDL_BUTTON_LEFT:
		if (_selectionMode == SelectionMode::SELECT)
		{
			pos = _mainCamera.convertScreenToWorld(glm::vec2(evnt.button.x, evnt.button.y));
			switch (_objectMode) {
			case ObjectMode::PLATFORM:
				
				if (_selectedBoxIdx == -1)
				{//If there is no selected box
					for (size_t i = 0; i < _boxes.size(); i++)
					{
						//Check if we are clicking the box
						if (_boxes[i].testPoint(pos.x, pos.y))
						{
							std::cout << "Box selected!   ";
							_selectedBoxIdx = i;

							//Update dims and rotation spinners
							if (_widthSpinner->getCurrentValue() != _boxes[_selectedBoxIdx].getDimensions().x) {
								_xChangedOnSelection = true;
								_widthSpinner->setCurrentValue(_boxes[_selectedBoxIdx].getDimensions().x);
								
							}
							if (_heightSpinner->getCurrentValue() != _boxes[_selectedBoxIdx].getDimensions().y) {
								_yChangedOnSelection = true;
								_heightSpinner->setCurrentValue(_boxes[_selectedBoxIdx].getDimensions().y);
								
							}
							if (_rotationSpinner->getCurrentValue() != _boxes[_selectedBoxIdx].getBody()->GetAngle()) {
								_rotationChangedOnSelection = true;
								_rotationSpinner->setCurrentValue(_boxes[_selectedBoxIdx].getBody()->GetAngle());
							}

							//Update color sliders
							if (_rSlider->getCurrentValue() != _boxes[_selectedBoxIdx].getColor().r)
							{
								_rValueChangedOnSelecion = true;
								_rSlider->setCurrentValue(_boxes[_selectedBoxIdx].getColor().r);
							}
							if (_gSlider->getCurrentValue() != _boxes[_selectedBoxIdx].getColor().g)
							{
								_gValueChangedOnSelecion = true;
								_gSlider->setCurrentValue(_boxes[_selectedBoxIdx].getColor().g);
							}
							if (_bSlider->getCurrentValue() != _boxes[_selectedBoxIdx].getColor().b)
							{
								_bValueChangedOnSelecion = true;
								_bSlider->setCurrentValue(_boxes[_selectedBoxIdx].getColor().b);
							}

							break;
						}
					}
				}
				else
				{//If there is a selected box
					_selectedBoxIdx = -1;
				}
				break;
			case ObjectMode::PLAYER:
				break;
			case ObjectMode::LIGHT:
				if (_selectedLightIdx == -1)
				{//If there is no selected light
					for (size_t i = 0; i < _lights.size(); i++)
					{
						if (abs(pos.x - _lights[i].position.x) <= smaallLightCircleSize && abs(pos.y - _lights[i].position.y) <= smaallLightCircleSize)
						{
							std::cout << "Light selected!   ";
							_selectedLightIdx = i;
						}
					}
				}
				else
				{//If there is a selected light
					_selectedLightIdx = -1;
				}
				break;
			case ObjectMode::FINISH:
				break;
			}
		}
		else //_selectionMode = SelectionMode::PLACE
		{
			Box newBox;
			BasicLight newLight;
			switch (_objectMode) {
			case ObjectMode::PLATFORM:
				pos = _mainCamera.convertScreenToWorld(glm::vec2(evnt.button.x, evnt.button.y));
				uvRect.x = pos.x;
				uvRect.y = pos.y;
				uvRect.z = _boxDims.x;
				uvRect.w = _boxDims.y;
				newBox.init(_world.get(), pos, _boxDims, texture, BasicEngine::Color((GLubyte)_colorPickerRed, (GLubyte)_colorPickerGreen, (GLubyte)_colorPickerBlue, 255),
					false ,_physicsMode == PhysicsMode::DYNAMIC, _boxRotation, uvRect);
				_boxes.push_back(newBox);
				break;
			case ObjectMode::PLAYER:
				pos = _mainCamera.convertScreenToWorld(glm::vec2(evnt.button.x, evnt.button.y));
				if (_player != nullptr)
				{
					_player->destroy(_world.get());
					delete _player;
					_player = nullptr;
				}
				_player = new Player();
				_player->init(_world.get(), pos, glm::vec2(2.0f), glm::vec2(1.0f, 1.8f), BasicEngine::Color(_colorPickerRed, _colorPickerGreen, _colorPickerBlue, 255));
				break;
			case ObjectMode::LIGHT:
				pos = _mainCamera.convertScreenToWorld(glm::vec2(evnt.button.x, evnt.button.y));
				newLight.init(BasicEngine::Color((GLubyte)_colorPickerRed, (GLubyte)_colorPickerGreen, (GLubyte)_colorPickerBlue, _lightIntensity), pos, _lightSize);
				_lights.push_back(newLight);
				break;
			case ObjectMode::FINISH:
				break;

			}
		}
		break;
	case SDL_BUTTON_RIGHT:
		break;
	}

}

void EditorScreen::updateMouseUp(SDL_Event evnt)
{
}

void EditorScreen::updateMouseMotion(SDL_Event evnt)
{
	// If right button is down, drag camera
	const float SPEED = 0.03f;
	if (_game->inputManager.isKeyDown(SDL_BUTTON_RIGHT)) {
		_mainCamera.offsetPosition(glm::vec2(-evnt.motion.xrel, evnt.motion.yrel * _mainCamera.getAspectRatio()) * SPEED);
	}

	//Update the position of the selected item
	if (_selectionMode == SelectionMode::SELECT) {
		switch (_objectMode)
		{
		case ObjectMode::PLAYER:
			break;
		case ObjectMode::PLATFORM:
			if (_selectedBoxIdx != -1)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				glm::vec2 pos = _mainCamera.convertScreenToWorld(glm::vec2(x, y));
				_boxes[_selectedBoxIdx].getBody()->SetTransform(b2Vec2(pos.x, pos.y), _boxRotation);
			}
			break;
		case ObjectMode::LIGHT:
			if (_selectedLightIdx != -1)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				glm::vec2 pos = _mainCamera.convertScreenToWorld(glm::vec2(x, y));
				_lights[_selectedLightIdx].position = pos;
			}
				break;
		case ObjectMode::FINISH:
			break;
		}
	}
}

bool EditorScreen::onBackClicked(const CEGUI::EventArgs& e)
{
	_currentState = BasicEngine::ScreenState::CHENG_PREVIOUS;

	return true;
}

bool EditorScreen::onColorPickerRedChanged(const CEGUI::EventArgs& e)
{
	_colorPickerRed = _rSlider->getCurrentValue();

	if (_rValueChangedOnSelecion)
		_rValueChangedOnSelecion = false;
	else
		updateSelectedBox();

	updateSelectedLight();
	return true;
}

bool EditorScreen::onColorPickerGreenChanged(const CEGUI::EventArgs& e)
{
	_colorPickerGreen = _gSlider->getCurrentValue();

	if (_gValueChangedOnSelecion)
		_gValueChangedOnSelecion = false;
	else
		updateSelectedBox();

	updateSelectedLight();
	return true;
}

bool EditorScreen::onColorPickerBlueChanged(const CEGUI::EventArgs& e)
{
	_colorPickerBlue = _bSlider->getCurrentValue();

	if (_bValueChangedOnSelecion)
		_bValueChangedOnSelecion = false;
	else
		updateSelectedBox();

	updateSelectedLight();
	return true;
}

bool EditorScreen::onRigidButtonClicked(const CEGUI::EventArgs& e)
{
	_physicsMode = PhysicsMode::RIGID;
	return true;
}

bool EditorScreen::onDynamicButtonClicked(const CEGUI::EventArgs& e)
{
	_physicsMode = PhysicsMode::DYNAMIC;
	return true;
}

bool EditorScreen::onPlayerButtonClicked(const CEGUI::EventArgs& e)
{
	setPlatformWidgetsVisibility(false);
	setLightWidgetsVisibility(false);

	deleteSelectedItem();
	_objectMode = ObjectMode::PLAYER;
	return true;
}

bool EditorScreen::onPlatformButtonClicked(const CEGUI::EventArgs& e)
{
	setPlatformWidgetsVisibility(true);
	setLightWidgetsVisibility(false);

	deleteSelectedItem();
	_objectMode = ObjectMode::PLATFORM;
	return true;
}

bool EditorScreen::onLightButtonClicked(const CEGUI::EventArgs& e)
{
	setPlatformWidgetsVisibility(false);
	setLightWidgetsVisibility(true);

	deleteSelectedItem();
	_objectMode = ObjectMode::LIGHT;
	return true;
}

bool EditorScreen::onSelectButtonClicked(const CEGUI::EventArgs& e)
{
	_selectionMode = SelectionMode::SELECT;
	return true;
}

bool EditorScreen::onPlaceButtonClicked(const CEGUI::EventArgs& e)
{
	_selectionMode = SelectionMode::PLACE;
	deleteSelectedItem();
	return true;
}

bool EditorScreen::onWidthValueChange(const CEGUI::EventArgs& e)
{
	_boxDims.x = (float)_widthSpinner->getCurrentValue();

	if (_xChangedOnSelection)
		_xChangedOnSelection = false;
	else
		updateSelectedBox();

	return true;
}

bool EditorScreen::onHeightValueChange(const CEGUI::EventArgs& e)
{
	_boxDims.y = (float)_heightSpinner->getCurrentValue();

	if (_yChangedOnSelection)
		_yChangedOnSelection = false;
	else
		updateSelectedBox();

	return true;
}

bool EditorScreen::onRotationValueChange(const CEGUI::EventArgs& e)
{
	_boxRotation = (float)_rotationSpinner->getCurrentValue();

	if (_rotationChangedOnSelection)
		_rotationChangedOnSelection = false;
	else
		updateSelectedBox();

	return true;
}

bool EditorScreen::onLightIntensityValueChange(const CEGUI::EventArgs& e)
{
	_lightIntensity = _lightIntensitySpinner->getCurrentValue();
	updateSelectedLight();
	return true;
}
bool EditorScreen::onLightSizeValueChange(const CEGUI::EventArgs& e)
{
	_lightSize = _lightSizeSpinner->getCurrentValue();
	updateSelectedLight();
	return true;
}

bool EditorScreen::onDebugToggleClicked(const CEGUI::EventArgs& e)
{
	_debugRender = _debugToggle->isSelected();
	return true;
}