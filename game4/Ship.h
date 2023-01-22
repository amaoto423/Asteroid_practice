#pragma once
#pragma once
#include "Actor.h"
class Ship :public Actor {
public:
	Ship(class Game* game);
	void UpdateActor(float deltatime)override;
	//void ProcessKeyBoard(const uint8_t* state);
private:
	
};