#pragma once

#include <map>

#include "Entity/IObject.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/OrientedRect2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class SpriteAnimator2D;
class TextureAtlas2D;

/** �÷��̾ ���ؾ� �� ���Դϴ�. */
class Fire : public IObject
{
public:
	/** �ִϸ��̼� �����Դϴ�. */
	enum EAnimationState
	{
		BURN = 0x00,      // ��Ÿ�� ����.
		EXPLOSION = 0x01, // ���� ����.
	};

public:
	Fire(const glm::vec2& position, const glm::vec2& direction, float speed, float lifeTime);
	virtual ~Fire();

	DISALLOW_COPY_AND_ASSIGN(Fire);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** ���� �浹 ������ ����ϴ�. */
	const Circle2D* GetCollisionBound() { return &collisionBound_; }

private:
	/** ���� �����Դϴ�. */
	void Move(float deltaSeconds);

	/** ���� �ִϸ��̼� ���¸� �ʱ�ȭ�մϴ�. */
	void LoadAnimations();

	/** ���� �ִϸ��̼� ���� �ʱ�ȭ�� �����մϴ�. */
	void UnloadAnimation();

private:
	/** �� ������ �� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;
	
	/** ������ �����Դϴ�. */
	OrientedRect2D renderBound_;

	/** �浹 �����Դϴ�. */
	Circle2D collisionBound_;

	/** ���� �̵� �����Դϴ�. */
	glm::vec2 direction_ = glm::vec2(0.0f, 0.0f);

	/** ���� �̵� �ӵ��Դϴ�. */
	float speed_ = 0.0f;

	/** ���� ������ Ÿ���Դϴ�. */
	float lifeTime_ = 0.0f;

	/** �ִϸ��̼� �����Դϴ�. */
	EAnimationState animationState_ = EAnimationState::BURN;

	/** ���� ���� �� �ִϸ��̼��Դϴ�. */
	std::map<EAnimationState, SpriteAnimator2D*> animations_;
};