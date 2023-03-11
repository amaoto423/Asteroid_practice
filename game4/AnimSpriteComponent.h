#pragma once
#include"SpriteComponent.h"
#include<vector>
#include"Texture.h"
class AnimSpriteComponent :public SpriteComponent {

public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	void Update(float deltatime)override;
	void SetAnimTextures(const std::vector<class Texture*>& textures);
	float GetAnimFPS()const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }


private:
	std::vector<class Texture*>mAnimTextures;
	float mAnimFPS;
	float mCurrFrame;
}; 
