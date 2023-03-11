#include"Texture.h"
#include"SOIL.h"
#include"GLEW.h"
#include"SDL.h"
Texture::Texture()
	:mTextureID(0)
	, mWidth(0)
	, mHeight(0)
{

}

Texture::~Texture()
{

}
bool Texture::Load(const std::string& fileName) {
	int channel = 0;
	unsigned char* image = SOIL_load_image(fileName.c_str(),
		&mWidth, &mHeight, &channel, SOIL_LOAD_AUTO);
	if (image == nullptr) {
		SDL_Log("The Texture %s can't Loaded", fileName.c_str());
		return false;
	}
	int format = GL_RGB;
	if (channel == 4) {
		format = GL_RGBA;
	}
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format,GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return true;
}
void Texture::Unload() {
	glDeleteTextures(1, &mTextureID);
}
void Texture::SetActive() {
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}