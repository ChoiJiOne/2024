#pragma once

#include <glm/glm.hpp>

#include "Entity/IEntity.h"

/** 페이드 효과를 제어하는 엔티티입니다. */
class FadeEffector : public IEntity
{
public:
	/** 페이드 효과를 제어하는 엔티티의 상태입니다. */
	enum class EState
	{
		WAIT     = 0x00, // 페이드 효과를 적용하지 않은 상태.
		PROGRESS = 0x01, // 페이드 효과를 적용 중인 상태.
		DONE     = 0x02, // 페이드 효과가 적용 완료된 상태.
	};

public:
	FadeEffector();
	virtual ~FadeEffector();

	DISALLOW_COPY_AND_ASSIGN(FadeEffector);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

	/** 페이드 인 효과(화면이 어두었다가 서서히 밝아지는)를 시작합니다. */
	void StartIn(float time);

	/** 페이드 아웃 효과(화면이 밝았다가 서서이 어두어지는)를 시작합니다. */
	void StartOut(float time);

	/** 현재 페이드 효과의 상태를 얻습니다. */
	const EState& GetState() const { return state_; }

	/** 페이드 효과를 적용 할 색상을 얻습니다. */
	const glm::vec3& GetBlendColor() const { return blendColor_; }

	/** 페이드 효과를 적용할 색상의 가중치 값을 얻습니다.  */
	float GetFactor() const { return factor_; }

	/** 페이드 효과의 상태를 초기화합니다. */
	void Reset();

private:
	/** 페이드 효과의 종류입니다. */
	enum class EType
	{
		NONE     = 0x00,
		FADE_IN  = 0x01,
		FADE_OUT = 0x02,
	};

private:
	/** 페이드 효과 적용 시 프레임 버퍼에 블랜딩할 색상입니다. 이 색상은 검정색 고정입니다. */
	glm::vec3 blendColor_ = glm::vec3(0.0f, 0.0f, 0.0f);

	/**
	 * 페이드 효과 적용 시 색상의 가중치 값입니다. 0.0이면 색상을 혼합하지 않고, 1.0이면 혼합 색상만 표시합니다.
	 * 0.0 => Fade In
	 * 1.0 => Fade Out
	 */
	float factor_ = 0.0f;

	/** 페이드 효과 적용 시간 값입니다. */
	float effectTime_ = 0.0f;

	/** 페이드 효과 적용 전체 시간 값입니다. */
	float maxEffectTime_ = 0.0f;

	/** 현재 페이드 효과의 상태입니다. */
	EState state_ = EState::WAIT;

	/** 현재 페이드 효과입니다. */
	EType type_ = EType::NONE;
};