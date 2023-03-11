#include"AIComponent.h"
#include"AIState.h"
AIComponent::AIComponent(class  Actor* owner):Component(owner){}

void AIComponent::Update(float deltatime) {
	if (mCurrentState) {
		mCurrentState->Update(deltatime);
	}
}
void AIComponent::ChangeState(const std::string& name) {
	mCurrentState->OnExit();
	mCurrentState = mStatesMap[name];
	mCurrentState->OnEnter();
}


void AIComponent::RegisterState(class AIState* state) {
	mStatesMap.emplace(state->GetName(), state);
}