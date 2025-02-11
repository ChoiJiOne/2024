#pragma once

#include <map>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class SpriteAnimator2D;

/** Ÿ��Ʋ ȭ�� ���� ���� ��ƼƼ�Դϴ�. */
class TitleFox : public IEntity2D
{
public:
	TitleFox();
	virtual ~TitleFox();

	DISALLOW_COPY_AND_ASSIGN(TitleFox);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** ������ ���¸� �ʱ�ȭ�մϴ�. */
	void Reset();

	/** ���찡 ȭ�� ������ �޸��ϴ�. */
	void RunWayout();

private:
	/** ������ �����Դϴ�. */
	enum class EState
	{
		IDLE = 0x00,
		RUN  = 0x01,
	};

	/** ������ �׸����Դϴ�. */
	struct Shadow
	{
		Rect2D bound; /** �׸��� �����Դϴ�. */
		TextureDrawOption option; /** �׸��� ������ �� ������ �ɼ��Դϴ�. */
		float scale = 0.0f; /** �׸����� ������ ���Դϴ�. */
	};

	/** �ִϸ��̼��� �ʱ�ȭ�մϴ�. */
	void LoadAnimations();

	/** �ִϸ��̼��� �����մϴ�. */
	void UnloadAnimations();

private:
	/** ������ �����Դϴ� */
	Rect2D renderBound_;

	/** ������ ������ �ɼ��Դϴ�. */
	TextureDrawOption renderOption_;

	/** ������ �׸����Դϴ�. */
	Shadow shadow_;

	/** ���� ������ �����Դϴ�. */
	EState state_ = EState::IDLE;

	/** ������ �޸��� �����Դϴ�. */
	glm::vec2 direction_ = glm::vec2(1.0f, 0.0f);

	/** ������ �޸��� �ӵ��Դϴ�. */
	float speed_ = 0.0f;

	/** ������ ��� ��������Ʈ �ִϸ��̼��Դϴ�. */
	std::map<EState, SpriteAnimator2D*> animations_;
};