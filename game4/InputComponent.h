#pragma once
#include"Actor.h"
#include "MoveComponent.h"

class InputComponent :public MoveComponent{
public:
	InputComponent(class Actor* owner);
	void ProcessInput(const uint8_t* keyState) override;
	//ゲッターセッター

	void SetMaxForwardSpeed(float FSpeed) {
		mMaxForwardSpeed = FSpeed;
	}
	void SetMaxAngularSpeed(float ASpeed) {
		mMaxAngularSpeed = ASpeed;
	}
	void SetForwardKey(int FK) {
		mForwardkey = FK;
	}
	void SetBackKey(int BK) {
		mBackKey = BK;
	}
	void SetClockWiseKey(int CK) {
		mClockwiseKey = CK;
	}
	void SetCounterClockwiseKey(int CCK) {
		mCounterClockwiseKey = CCK;
	}

	float GetForwardSpeed() {
		return mMaxForwardSpeed;
	}
	float GetAngularSpeed() {
		return mMaxAngularSpeed;
	}
private:
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	int mForwardkey;
	int mBackKey;
	int mClockwiseKey;
	int mCounterClockwiseKey;


};