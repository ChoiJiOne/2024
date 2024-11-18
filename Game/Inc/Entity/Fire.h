#pragma once

#include <map>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/OrientedRect2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class SpriteAnimator2D;
class TextureAtlas2D;
class Player;
class Playground;

/** �÷��̾ ���ؾ� �� ���Դϴ�. */
class Fire : public IEntity2D
{
public:
	/** ���� �����Դϴ�. */
	enum class EState
	{
		NONE      = 0x00, // �ƹ��͵� �ƴ� ����.
		MOVE      = 0x01, // �����̰� �ִ� ����.
		EXPLOSION = 0x02, // ���� �����ϴ� ����.
		DONE      = 0x03, // �� �̻� ������Ʈ�� �� ���� ����.
	};

public:
	Fire(const glm::vec2& position, const glm::vec2& direction, float speed);
	virtual ~Fire();

	DISALLOW_COPY_AND_ASSIGN(Fire);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** ���� ���� ���¸� ����ϴ�. */
	const EState& GetState() const { return state_; }

private:
	/** ���� �����Դϴ�. */
	void Move(float deltaSeconds);

private:
	/** ���� ������ �� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;
	
	/** �ش� ������ ȹ���ߴ��� Ȯ���� �÷��̾��Դϴ�. */
	Player* player_ = nullptr;

	/** ���� ������ �����Դϴ�. */
	Playground* playground_ = nullptr;

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

	/** ���� ���� �����Դϴ�. */
	EState state_ = EState::NONE;

	/** ���� ���� �� �ִϸ��̼��Դϴ�. */
	std::map<EState, SpriteAnimator2D*> animations_;
};