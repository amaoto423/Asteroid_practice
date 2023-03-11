#pragma once
#include<string>
class Texture {
public:
	Texture();
	~Texture();
	bool Load(const std::string& fileNmame);
	void Unload();
	void SetActive();
	int GetWidrth()const { return mWidth; }
	int GetHeight()const { return mHeight; }

private:
	int mWidth, mHeight;
	unsigned int mTextureID;
};