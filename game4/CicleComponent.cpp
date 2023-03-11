#include"CircleComponent.h"
#include "Component.h"
#include"Actor.h"

CircleComponent::CircleComponent(class Actor* owner,int updateorder):Component(owner, updateorder),mRadius(0) {

}
const Vector2& CircleComponent::GetCenter() const {
	return  mOwner->GetPosition();
	
	
}