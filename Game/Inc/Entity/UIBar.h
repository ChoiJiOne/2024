#pragma once

#include <string>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class TTFont;
class UICamera;

/** UI 엔티티입니다. */
class UIBar : public IEntity2D
{
public:
	UIBar(UICamera* uiCamera, TTFont* font);
	virtual ~UIBar();

	DISALLOW_COPY_AND_ASSIGN(UIBar);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 플레이어의 현재 HP를 얻습니다. */
	float GetBar() const { return bar_; }

	/** 플레이어의 HP 값을 설정합니다. */
	void SetBar(float bar);

private:
	/** UI바 렌더링에 기준이 될 UI 카메라입니다. */
	UICamera* uiCamera_ = nullptr;

	/** UI바에 텍스트를 렌더링할 때 참조할 폰트입니다. */
	TTFont* font_ = nullptr;

	/** UI바의 백그라운드 크기입니다. */
	Rect2D background_;

	/** UI바의 영역입니다. */
	Rect2D barBound_;

	/** UI바의 백그라운드 색상입니다. */
	glm::vec4 backgroundColor_;

	/** UI바의 체력 색상입니다. */
	glm::vec4 barColor_;

	/** 플레이어의 HP입니다. */
	float bar_ = 0.0f;

	/** 플레이어의 HP 렌더링 시 부드러운 전환을 위한 마크입니다. */
	float barMark_ = 0.0f;

	/** 플레이어의 최소 HP입니다. */
	float minBar_ = 0.0f;

	/** 플레이어의 최대 HP입니다. */
	float maxBar_ = 0.0f;

	/** 플레이어의 HP 렌더링 시 부드러운 전환을 위한 속도입니다. */
	float barSlideSpeed_ = 0.0f;

	/** UI바에 표시할 텍스트입니다. */
	std::wstring text_;
};