#include "Camera2D.h"

namespace BasicEngine {
	Camera2D::Camera2D()
		: _position(0.0f, 0.0f), _cameraMatrix(1.0f), _orthoMatrix(1.0f), _scale(1.0f), _needsMatrixUpdate(true), _screenWidth(500), _screenHeight(500)
	{

	}
	Camera2D::~Camera2D()
	{

	}

	void Camera2D::init(int screenWidth, int screenHeight)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	void Camera2D::update()
	{
		if (_needsMatrixUpdate)
		{
			//Camera Translation
			glm::vec3 translateVector(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translateVector);

			//Camera Scale
			glm::vec3 scaleVector(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scaleVector) * _cameraMatrix;
			
			_needsMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords)
	{
		//Invert y coords
		screenCoords.y = _screenHeight - screenCoords.y;
		
		//Make it so 0,0 is at the middle of the screen
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);

		//Scale the coordinates with the camera
		screenCoords /= _scale;

		//Translate the coordinates with the camera position
		screenCoords += _position;

		return screenCoords;
	}

	//A collision test to see if a box is in the camera view
	bool Camera2D::isBoxInView(const glm::vec2& pos, const glm::vec2& dimensions)
	{
		//Take scale into account scale
		glm::vec2 scaledDimensions = glm::vec2( _screenWidth, _screenHeight) / _scale;

		//The minimum distance between the camera and the box in x and y directions
		const float MIN_DISTANCE_X = dimensions.x/2.0f + scaledDimensions.x / 2.0f;
		const float MIN_DISTANCE_Y = dimensions.y/2.0f + scaledDimensions.y / 2.0f;

		//The center pos of the box
		glm::vec2 centerPos = pos + dimensions/2.0f;
		//The center pos of the camera
		glm::vec2 centerCameraPos = _position;
		//The distance vector between the centers of the box and the camera
		glm::vec2 distVec = centerPos - centerCameraPos;

		//The depth of the collision in x and y directions
		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

		//If this is true we are colliding
		if (xDepth > 0 && yDepth > 0)
		{
			//There was a collision
			return true;
		}

		//There wasn't a collision
		return false;
	}
}