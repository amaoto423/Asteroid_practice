#pragma once
#include "Component.h"
#include<string>
#include<unordered_map>
class AIComponent:public Component {
public:
	AIComponent(class Actor* owner);
	void Update(float deltatime)override;
	void ChangeState(const std::string& name);
	void RegisterState(class AIState* state);

private:
	std::unordered_map<std::string, AIState*> mStatesMap;
	class AIState* mCurrentState;
};