#include"Ship.h"
#include"SpriteComponent.h"
#include"game.h"
#include"vector"
#include"Laser.h"
#include"InputComponent.h"
Ship::Ship(Game* game) :Actor(game),mLaserCooldown(0) {
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
	mLaserCooldown -= deltatime;
}

void Ship::ActorInput(const uint8_t* keystate) {
	if (keystate[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0) {
		//LaserƒNƒ‰ƒXì‚ç‚È‚«‚ác
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetScale(1);
		laser->SetRotation(GetRotation());
		mLaserCooldown = 0.5f;
	}
}
