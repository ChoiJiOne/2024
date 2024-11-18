#pragma once

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class UICamera;

/** 플레이어의 HP를 표시하는 UI 엔티티입니다. */
class HPBar : public IEntity2D
{
public:
	HPBar(UICamera* uiCamera);
	virtual ~HPBar();

	DISALLOW_COPY_AND_ASSIGN(HPBar);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 플레이어의 현재 HP를 얻습니다. */
	float GetHP() const { return hp_; }

	/** 플레이어의 HP 값을 설정합니다. */
	void SetHP(float hp);

private:
	/** HP바 렌더링에 기준이 될 UI 카메라입니다. */
	UICamera* uiCamera_ = nullptr;

	/** HP바의 백그라운드 크기입니다. */
	Rect2D background_;

	/** HP바의 영역입니다. */
	Rect2D hpBound_;

	/** HP바의 백그라운드 색상입니다. */
	glm::vec4 backgroundColor_;

	/** HP바의 체력 색상입니다. */
	glm::vec4 hpColor_;

	/** 플레이어의 HP입니다. */
	float hp_ = 0.0f;

	/** 플레이어의 HP 렌더링 시 부드러운 전환을 위한 마크입니다. */
	float hpMark_ = 0.0f;

	/** 플레이어의 최소 HP입니다. */
	float minHp_ = 0.0f;

	/** 플레이어의 최대 HP입니다. */
	float maxHp_ = 0.0f;

	/** 플레이어의 HP 렌더링 시 부드러운 전환을 위한 속도입니다. */
	float hpSpeed_ = 0.0f;
};