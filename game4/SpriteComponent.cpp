#include"SpriteComponent.h"
#include"game.h"
#include"Actor.h"
#include"Math.h"
#include"Texture.h"
SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	, mTexture(nullptr)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(class Texture* texture) {
	mTexture = texture;
	mTexWidth = texture->GetWidrth();
	mTexHeight = texture->GetHeight();

}
void SpriteComponent::Draw(Shader* shader) {
	Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0);

	Matrix4 world = scaleMat * mOwner->GetWorldTransform();
	shader->SetMatrixUniform("uWorldTransform", world);
	mTexture->SetActive();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
