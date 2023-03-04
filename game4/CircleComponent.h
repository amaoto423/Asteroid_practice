#pragma once
#include"Component.h"
#include"Math.h"

class CircleComponent :public Component {
public:
	CircleComponent(class Actor* owner,int updateorder=10);
	void SetRadius(float rad) { mRadius = rad; }
	float GetRadius() const { return mRadius; }
	const Vector2& GetCenter() const;
private:
	float mRadius;
};
