#include"Ship.h"
#include"SpriteComponent.h"
#include"game.h"
#include"vector"
#include"InputComponent.h"
Ship::Ship(Game* game) :Actor(game) {
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_D);
	ic->SetBackKey(SDL_SCANCODE_A);
	ic->SetClockWiseKey(SDL_SCANCODE_W);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_S);
	ic->SetMaxForwardSpeed(300);
	ic->SetMaxAngularSpeed(10);
}

void Ship::UpdateActor(float deltatime) {
	Actor::UpdateActor(deltatime);
	
}


