#pragma once

#include <functional>
#include <string>

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class TTFont;
class UICamera;

/** UI ��ư�Դϴ�. */
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
	/** UI ��ư�� �����Դϴ�. */
	enum class EButtonPress : int32_t
	{
		DISABLED = 0x00,
		ENABLED  = 0x01,
		PRESSED  = 0x02,
		RELEASED = 0x03,
	};

private:
	/** UI ��ư�� �Է� �� �������� ������ �� UI ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** UI ��ư�� �ؽ�Ʈ�� �������� �� ������ ��Ʈ�Դϴ�. */
	TTFont* font_ = nullptr;

	/** UI ��ư�� ��׶��� ũ���Դϴ�. */
	Rect2D background_;
};