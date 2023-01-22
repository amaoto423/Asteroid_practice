#include "InputComponent.h"

InputComponent::InputComponent(class Actor* owner):MoveComponent(owner),mMaxAngularSpeed(0),mMaxForwardSpeed(0),mForwardkey(0),mBackKey(0),mClockwiseKey(0),mCounterClockwiseKey(0) {

}

void InputComponent::ProcessInput(const uint8_t* keyState) {
	float forwardSpeed = 0;
	if (keyState[mForwardkey]) {
		forwardSpeed += mMaxForwardSpeed;
}
	if (keyState[mBackKey]) {
		forwardSpeed -= mMaxForwardSpeed;
	}
	SetForwardSpeed(forwardSpeed);
	float angularSpeed = 0;
	if (keyState[mClockwiseKey]) {
		angularSpeed += mMaxAngularSpeed;
	}
	if (keyState[mCounterClockwiseKey]) {
		angularSpeed -= mMaxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed);

}