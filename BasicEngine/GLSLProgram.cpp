#include "GLSLProgram.h"
#include "Errors.h"
#include "IOManager.h"

#include <fstream>
#include <vector>

namespace BasicEngine {
	GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0)
	{

	}
	GLSLProgram::~GLSLProgram()
	{

	}

	void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		std::string vertSource, fragSource;
		IOManager::readFileToBuffer(vertexShaderFilePath, vertSource);
		IOManager::readFileToBuffer(fragmentShaderFilePath, fragSource);

		compileShadersFromSource(vertSource.c_str(), fragSource.c_str());
	}

	void GLSLProgram::compileShadersFromSource(const char* vertexSource, const char* fragmentSource)
	{
		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		_programID = glCreateProgram();

		//Create the vertex shader
		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexShaderID == 0)
		{
			fatalError("Vertex shader failed to be created");
		}

		//Create the fragment shader
		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0)
		{
			fatalError("Fragment shader failed to be created");
		}

		compileShader(vertexSource, "Vertex Shader", _vertexShaderID);
		compileShader(fragmentSource, "Fragment Shader", _fragmentShaderID);
	}

	void GLSLProgram::linkShaders()
	{
		// Attach our shaders to our program
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		// Link our program
		glLinkProgram(_programID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);



			// We don't need the program anymore.
			glDeleteProgram(_programID);
			// Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to compile");
		}

		//Always detach shaders after a successful link.
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}

	//Adds an attribute to our shader. Should be called between compiling and linking
	void GLSLProgram::addAttribute(const std::string& attributeName)
	{
		glBindAttribLocation(_programID, _numAttributes, attributeName.c_str());
		_numAttributes++;
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
	{
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());

		if (location == GL_INVALID_INDEX)
			fatalError("Uniform " + uniformName + " not found in shader!");

		return location;
	}

	//Enable the shader and all its attributes
	void GLSLProgram::use()
	{
		glUseProgram(_programID);

		//enable all the attributes we added with addAttribute
		for (size_t i = 0; i < _numAttributes; i++)
			glEnableVertexAttribArray(i);
	}

	//Disable the shader and all its attributes
	void GLSLProgram::unuse()
	{
		glUseProgram(0);

		//diable all the attributes we added with addAttribute
		for (size_t i = 0; i < _numAttributes; i++)
			glDisableVertexAttribArray(i);

		_numAttributes = 0;
	}

	void GLSLProgram::dispose()
	{
		if(_programID)
			glDeleteProgram(_programID);
	}

	void GLSLProgram::compileShader(const char* source, const std::string& name, GLuint shaderID)
	{

		glShaderSource(shaderID, 1, &source, nullptr);

		glCompileShader(shaderID);

		GLint success = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(shaderID); // Don't leak the shader.

			std::printf("%s\n", &(errorLog[0]));
			fatalError(name + "failed to compile");
		}
	}
}