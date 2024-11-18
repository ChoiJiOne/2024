#pragma once

#include "Entity/IObject.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class SpriteAnimator2D;
class TextureAtlas2D;

/** �÷��̾ ȹ���� �����Դϴ�. */
class Coin : public IObject
{
public:
	Coin(const glm::vec2& startPos, const glm::vec2& endPos);
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

	/** ������ �����Դϴ�. */
	void Move(float deltaSeconds);

private:
	/** ���� ������ �� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** ������ �ִϸ��̼��� �����ϴ� ��������Ʈ �ִϸ������Դϴ�. */
	SpriteAnimator2D* animator_ = nullptr;

	/** ������ �̵� ���� ��ġ�Դϴ�. */
	glm::vec2 moveStartPos_ = glm::vec2(0.0f, 0.0f);
	
	/** ������ �̵� �� ��ġ�Դϴ�. */
	glm::vec2 moveEndPos_ = glm::vec2(0.0f, 0.0f);
	
	/** ������ �����Դϴ�. */
	Rect2D renderBound_;

	/** �浹 �����Դϴ�. */
	Circle2D collisionBound_;

	/** ������ �׸����Դϴ�. */
	Shadow shadow_;

	/** ������ �̵� �ð��Դϴ�. */
	float moveTime_ = 0.0f;

	/** ������ �ִ� �̵� �ð��Դϴ�. */
	float maxMoveTime_ = 0.0f;
};