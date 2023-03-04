#pragma once
#include"CircleComponent.h"
#include"Actor.h"
class Laser :public Actor {
public:
	Laser(Game* game);
	void UpdateActor(float deltatime)override;
private:
	class CircleComponent* mCircle;
	float mLivetime = 1.0f;
};