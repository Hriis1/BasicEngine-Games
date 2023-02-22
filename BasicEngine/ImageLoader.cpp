#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"

#include <vector>
namespace BasicEngine {
	GLTexture ImageLoader::loadPNG(const std::string& filePath)
	{
		GLTexture texture = { 0,0,0 };

		std::vector<unsigned char> in;
		std::vector<unsigned char> out;

		unsigned long width, height;

		if (IOManager::readFileToBuffer(filePath, in) == false)
		{
			fatalError("Failed to load PNG file to buffer");
		}

		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
		if (errorCode != 0)
		{
			fatalError("decodePNG failed with error: " + std::to_string(errorCode));
		}

		//Generate a openGL texture
		glGenTextures(1, &(texture.id));

		//Bind the openGL texture
		glBindTexture(GL_TEXTURE_2D, texture.id);

		//Upload the image data to the openGL texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//Generate the mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);

		//Unbind the openGL texture
		glBindTexture(GL_TEXTURE_2D, 0);

		//Set the textures width and height to the ones we generated
		texture.width = width;
		texture.height = height;

		return texture;
	}
}