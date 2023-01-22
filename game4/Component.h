#pragma once
#include <cstdint>

class Component {
public:
	Component(class Actor* owner, int updateOder = 100);
	virtual ~Component();
	virtual void Update(float deltatime);
	int GetUpdateOrder()const { return mUpdateOrder; }
	virtual void ProcessInput(const uint8_t* keyState) {}
protected:
	class Actor* mOwner;
	int mUpdateOrder;
};