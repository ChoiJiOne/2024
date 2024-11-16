#pragma once

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class SpriteAnimator2D;
class TextureAtlas2D;

/** �÷��̾ ȹ���� �����Դϴ�. */
class Coin : public IEntity2D
{
public:
	Coin(const glm::vec2& position);
	virtual ~Coin();

	DISALLOW_COPY_AND_ASSIGN(Coin);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** ������ �׸����Դϴ�. */
	struct Shadow
	{
		Rect2D bound; /** �׸��� �����Դϴ�. */
		TextureDrawOption option; /** �׸��� ������ �� ������ �ɼ��Դϴ�. */
		float scale = 0.0f; /** �׸����� ������ ���Դϴ�. */
	};

private:
	/** ���� ������ �� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** ������ �ִϸ��̼��� �����ϴ� ��������Ʈ �ִϸ������Դϴ�. */
	SpriteAnimator2D* animator_ = nullptr;

	/** ������ �����Դϴ�. */
	Rect2D renderBound_;

	/** �浹 �����Դϴ�. */
	Circle2D collisionBound_;

	/** ������ �׸����Դϴ�. */
	Shadow shadow_;
};