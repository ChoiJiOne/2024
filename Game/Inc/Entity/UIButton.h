#pragma once

#include <functional>
#include <string>

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class TTFont;
class UICamera;

/** UI 버튼입니다. */
class UIButton : public IEntity2D
{
public:
	UIButton(UICamera* uiCamera, TTFont* font);
	virtual ~UIButton();

	DISALLOW_COPY_AND_ASSIGN(UIButton);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** UI 버튼의 상태입니다. */
	enum class EButtonPress : int32_t
	{
		DISABLED = 0x00,
		ENABLED  = 0x01,
		PRESSED  = 0x02,
		RELEASED = 0x03,
	};

private:
	/** UI 버튼의 입력 및 렌더링에 기준이 될 UI 카메라입니다. */
	UICamera* uiCamera_ = nullptr;

	/** UI 버튼에 텍스트를 렌더링할 때 참조할 폰트입니다. */
	TTFont* font_ = nullptr;

	/** UI 버튼의 백그라운드 크기입니다. */
	Rect2D background_;
};