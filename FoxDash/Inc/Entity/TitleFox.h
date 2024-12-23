#pragma once

#include <map>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** 클래스 전방 선언입니다. */
class SpriteAnimator2D;

/** 타이틀 화면 내에 여우 엔티티입니다. */
class TitleFox : public IEntity2D
{
public:
	TitleFox();
	virtual ~TitleFox();

	DISALLOW_COPY_AND_ASSIGN(TitleFox);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 여우의 상태를 초기화합니다. */
	void Reset();

	/** 여우가 화면 밖으로 달립니다. */
	void RunWayout();

private:
	/** 여우의 상태입니다. */
	enum class EState
	{
		IDLE = 0x00,
		RUN  = 0x01,
	};

	/** 여우의 그림자입니다. */
	struct Shadow
	{
		Rect2D bound; /** 그림자 영역입니다. */
		TextureDrawOption option; /** 그림자 렌더링 시 설정할 옵션입니다. */
		float scale = 0.0f; /** 그림자의 스케일 값입니다. */
	};

	/** 애니메이션을 초기화합니다. */
	void LoadAnimations();

	/** 애니메이션을 해제합니다. */
	void UnloadAnimations();

private:
	/** 렌더링 영역입니다 */
	Rect2D renderBound_;

	/** 여우의 렌더링 옵션입니다. */
	TextureDrawOption renderOption_;

	/** 여우의 그림자입니다. */
	Shadow shadow_;

	/** 현재 여우의 상태입니다. */
	EState state_ = EState::IDLE;

	/** 여우의 달리기 방향입니다. */
	glm::vec2 direction_ = glm::vec2(1.0f, 0.0f);

	/** 여우의 달리기 속도입니다. */
	float speed_ = 0.0f;

	/** 여우의 대기 스프라이트 애니메이션입니다. */
	std::map<EState, SpriteAnimator2D*> animations_;
};