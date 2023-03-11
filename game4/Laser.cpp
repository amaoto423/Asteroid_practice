#include"Laser.h"
#include"MoveComponent.h"
#include"SpriteComponent.h"
#include"game.h"
#include"CircleComponent.h"
bool Intersect(const CircleComponent& a, const CircleComponent& b) {
	Vector2 dif = a.GetCenter() - b.GetCenter();
	float dist = dif.LengthSq();
	float rad = a.GetRadius() + b.GetRadius();
	rad *= rad;
	return dist <= rad;
}
Laser::Laser(Game* game):Actor(game) {
	SpriteComponent* sp = new SpriteComponent(this);
	sp->SetTexture(game->GetTexture("Assets/Laser.png"));
	MoveComponent* mv = new MoveComponent(this);
	mv->SetForwardSpeed(600.0f);
	mCircle= new CircleComponent(this);
	mCircle->SetRadius(10);
	
}
void Laser::UpdateActor(float deltatime) {
	for (auto ast : GetGame()->GetAsteroid()) {
		if (Intersect(*mCircle, *(ast->Getcircle()))) {
			SetState(EDead);
			ast->SetState(EDead);
			break;
		}
	}
	mLivetime -= deltatime;
	if (mLivetime <= 0) {
		SetState(EDead);
	}
}