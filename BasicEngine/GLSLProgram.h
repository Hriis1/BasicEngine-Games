#pragma once

#include <string>
#include <GL/glew.h>
namespace BasicEngine {
	class GLSLProgram
	{
	private:
		//The ID of the complete program
		GLuint _programID;

		//The ID of the vertex shader
		GLuint _vertexShaderID;
		//The ID of the fragment shader
		GLuint _fragmentShaderID;

		int _numAttributes;
	private:
		void compileShader(const char* source, const std::string& name, GLuint shaderID);
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);

		void linkShaders();

		void addAttribute(const std::string& attributeName);

		GLint getUniformLocation(const std::string& uniformName);

		void use();
		void unuse();

		void dispose();
	};

}