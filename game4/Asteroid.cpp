#include "Asteroid.h"
#include "Math.h"
#include "Random.h"
#include "SpriteComponent.h"
#include"MoveComponent.h"
#include"game.h"
Asteroid::Asteroid(Game* game) :Actor(game) {

	Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	SpriteComponent* sp = new SpriteComponent(this);
	sp->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);
}
Asteroid::~Asteroid()
{

}
