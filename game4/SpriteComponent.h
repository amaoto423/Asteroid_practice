#pragma once
#pragma once
#include"Component.h"
#include<SDL.h>
#include"Texture.h"
class SpriteComponent : public Component {
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(class Shader* shader);
	virtual void SetTexture(class Texture* texture);
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight()const { return mTexHeight; }
	int GetTexWidth()const { return mTexWidth; }
protected:
	int mDrawOrder;
	class Texture* mTexture;
	int mTexWidth;
	int mTexHeight;
};