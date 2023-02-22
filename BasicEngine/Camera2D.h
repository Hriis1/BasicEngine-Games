#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace BasicEngine {
	class Camera2D
	{
	private:
		bool _needsMatrixUpdate;
		int _screenWidth;
		int _screenHeight;

		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
		float _scale;
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight);

		void update();

		glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

		bool isBoxInView(const glm::vec2& pos, const glm::vec2& dimensions);

		void offsetPosition(const glm::vec2& offset) { _position += offset; _needsMatrixUpdate = true; }
		void offsetScale(float offset) { _scale += offset; if (_scale < 0.001f) { _scale = 0.001f; } _needsMatrixUpdate = true; }

		//getters
		glm::vec2 getPosition() { return _position; }
		float getScale() { return _scale; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }
		float getAspectRatio() const { return (float)_screenWidth / (float)_screenHeight; }

		//setters
		void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
		void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true;}
	};
}
