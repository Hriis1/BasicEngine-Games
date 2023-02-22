#pragma once

#include <IGameScreen.h>
#include <memory>
#include <map>
#include <vector>
#include <Camera2D.h>
#include <Window.h>
#include <GUI.h>
#include <GLSLProgram.h>
#include <SpriteBatch.h>
#include <DebugRenderer.h>
#include <InputManager.h>

#include "Box.h"
#include "ScreenIndices.h"
#include"Lighting.h"
#include "Player.h"

//SADASDASDASDASDASDASDASDASD
enum class PhysicsMode
{
	RIGID, DYNAMIC
};

enum class ObjectMode
{
	PLAYER, PLATFORM, LIGHT, FINISH
};

enum class SelectionMode
{
	SELECT, PLACE
};

const int NO_BOX = -1;
const int NO_LIGHT = -1;

class EditorScreen : public BasicEngine::IGameScreen
{
public:
	EditorScreen(BasicEngine::Window* window);
	~EditorScreen();

	// Inherited via IGameScreen
	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;
	virtual void build() override;
	virtual void destroy() override;
	virtual void onEntry() override;
	virtual void onExit() override;
	virtual void update() override;
	virtual void draw() override;

	void checkInput();

private:
	BasicEngine::Camera2D _mainCamera;
	BasicEngine::Camera2D _UIcamera;
	BasicEngine::Window* _window;
	BasicEngine::SpriteBatch _spriteBatch;
	BasicEngine::GLSLProgram _textureProgram;
	BasicEngine::GLSLProgram _lightProgram;
	BasicEngine::DebugRenderer _debugRenderer;

	GLuint _blankTexture = 0.0f;

	PhysicsMode _physicsMode = PhysicsMode::DYNAMIC;
	ObjectMode _objectMode = ObjectMode::PLATFORM;
	SelectionMode _selectionMode = SelectionMode::PLACE;

	bool _debugRender = false;

	glm::vec2 _boxDims;
	float _boxRotation = 0.0f;

	int _lightIntensity = 255;
	float _lightSize = 5.0f;

	std::unique_ptr<b2World> _world;
	std::vector<Box> _boxes;
	std::vector<BasicLight> _lights;

	int _selectedBoxIdx = -1;
	int _selectedLightIdx = -1;

	bool _xChangedOnSelection = false;
	bool _yChangedOnSelection = false;
	bool _rotationChangedOnSelection = false;
	bool _rValueChangedOnSelecion = false;
	bool _gValueChangedOnSelecion = false;
	bool _bValueChangedOnSelecion = false;

	Player* _player = nullptr;

	//UI stuff
	BasicEngine::GUI _gui;

	std::map<CEGUI::Window*, CEGUI::Window*> _labelMap;

	CEGUI::Window* _groupBox = nullptr;

	CEGUI::Slider* _rSlider = nullptr;
	CEGUI::Slider* _gSlider = nullptr;
	CEGUI::Slider* _bSlider = nullptr;
	float _colorPickerRed = 255.0f;
	float _colorPickerGreen = 255.0f;
	float _colorPickerBlue = 255.0f;

	CEGUI::RadioButton* _playerRadioButton = nullptr;
	CEGUI::RadioButton* _platformRadioButton = nullptr;
	CEGUI::RadioButton* _lightRadioButton = nullptr;
	CEGUI::RadioButton* _rigidRadioButton = nullptr;
	CEGUI::RadioButton* _dynamicRadioButton = nullptr;
	CEGUI::RadioButton* _selectRadioButton = nullptr;
	CEGUI::RadioButton* _placeRadioButton = nullptr;

	CEGUI::Spinner* _widthSpinner = nullptr;
	CEGUI::Spinner* _heightSpinner = nullptr;
	CEGUI::Spinner* _rotationSpinner = nullptr;
	CEGUI::Spinner* _lightSizeSpinner = nullptr;
	CEGUI::Spinner* _lightIntensitySpinner = nullptr;

	CEGUI::ToggleButton* _debugToggle = nullptr;

private:
	void updateObjectValues();
	void updateSelectedBox();
	void updateSelectedLight();
	void refreshSelectedBox(const glm::vec2& newPosition);
	void deleteSelectedItem();

	void initUI();
	void initShaders();

	void setPlatformWidgetsVisibility(bool visible);
	void setLightWidgetsVisibility(bool visible);

	bool isMouseInUI();

	void updateMouseDown(SDL_Event evnt);
	void updateMouseUp(SDL_Event evnt);
	void updateMouseMotion(SDL_Event evnt);

	void drawUI();
	void drawWorld();

	void resetWorld();
	void resetUI();

	void createLableForUIElement(CEGUI::Window* element, const std::string& text, float _xOffset = 0.0f, float _yOffset = 0.0f);
	//Event funcs
	bool onBackClicked(const CEGUI::EventArgs& e);

	bool onColorPickerRedChanged(const CEGUI::EventArgs& e);
	bool onColorPickerGreenChanged(const CEGUI::EventArgs& e);
	bool onColorPickerBlueChanged(const CEGUI::EventArgs& e);

	bool onRigidButtonClicked(const CEGUI::EventArgs& e);
	bool onDynamicButtonClicked(const CEGUI::EventArgs& e);
	bool onPlayerButtonClicked(const CEGUI::EventArgs& e);
	bool onPlatformButtonClicked(const CEGUI::EventArgs& e);
	bool onLightButtonClicked(const CEGUI::EventArgs& e);
	bool onSelectButtonClicked(const CEGUI::EventArgs& e);
	bool onPlaceButtonClicked(const CEGUI::EventArgs& e);

	bool onWidthValueChange(const CEGUI::EventArgs& e);
	bool onHeightValueChange(const CEGUI::EventArgs& e);
	bool onRotationValueChange(const CEGUI::EventArgs& e);
	bool onLightIntensityValueChange(const CEGUI::EventArgs& e);
	bool onLightSizeValueChange(const CEGUI::EventArgs& e);

	bool onDebugToggleClicked(const CEGUI::EventArgs& e);

};

