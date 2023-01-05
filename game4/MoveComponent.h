#pragma once
#include "Component.h"

class MoveComponent :public  Component {
public:
	MoveComponent(class Actor* owner, int updateorder = 10);
	void Update(float deltatime)override;

	float GetAngularSpeed() {
		return mAngularSpeed;
	}
	float GetForwardSpeed() {
		return mForwardSpeed;
	}
	void SetAngularSpeed(float speed) {
		mAngularSpeed = speed;
	}
	void SetForwardSpeed(float speed) {
		mForwardSpeed = speed;
	}

private:
	float mAngularSpeed;
	float mForwardSpeed;
};