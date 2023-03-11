#pragma once
#pragma once
#pragma once
#include "Math.h"
#include<vector>
#include <cstdint>
class Actor {
public:
	enum State {
		EActive, EPaused, EDead
	};
	Actor(class Game* game);
	virtual ~Actor();
	void Update(float deltaTime);
	void UpdateComponent(float deltaTime);
	virtual void UpdateActor(float deltaTime);
	//ゲッター・セッター
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { 
		ActivateRecomputeWorldTransform();
		mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) {
		ActivateRecomputeWorldTransform();
		mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { 
		ActivateRecomputeWorldTransform();
		mRotation = rotation; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState){};
	class Game* GetGame() { return mGame; }


	void addComponent(class Component* component);
	void RemoveComponent(class Component* component);
	Vector2 GetForward() {
		return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation));
	}
	void ComputeWorldTransform();
	void ActivateRecomputeWorldTransform() { mRecomputeWorldTransform = true; }
	Matrix4 GetWorldTransform() { return mWorldTransform; }
protected:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation;
	std::vector<class Component*> mComponents;
	class Game* mGame;
	Matrix4 mWorldTransform;
	bool mRecomputeWorldTransform;
};
