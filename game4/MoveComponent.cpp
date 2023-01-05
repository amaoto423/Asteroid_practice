#include"MoveComponent.h"
#include"Actor.h"
MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	, mAngularSpeed(0.0f)
	, mForwardSpeed(0.0f)
{

}
void MoveComponent::Update(float deltatime) {
	if (!Math::NearZero(mAngularSpeed)) {
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltatime;
		mOwner->SetRotation(rot);
	}
	if (!Math::NearZero(mForwardSpeed)) {
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltatime;
		if (pos.x < 0) {
			pos.x = 1024;
		}
		if (pos.x > 1024) {
			pos.x = 0;
		}
		if (pos.y > 768) {
			pos.y = 0;
		}
		if (pos.y < 0) {
			pos.y = 768;
		}
		mOwner->SetPosition(pos);
	}
}