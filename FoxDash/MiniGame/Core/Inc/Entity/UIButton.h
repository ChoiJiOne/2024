#pragma once

#include <functional>
#include <map>
#include <string>

#include "Entity/IEntity2D.h"
#include "GLFW/GLFWManager.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class TTFont;
class UICamera;

/** UI ��ư�Դϴ�. */
class UIButton : public IEntity2D
{
public:
	/** UI ��ư�� ���� �Ӽ��� �����ϱ� ���ؼ��� Json ������ ������ �ʿ��մϴ�. */
	UIButton(const std::string& buttonPath, UICamera* uiCamera, TTFont* font, const EMouse& mouse, const std::function<void()>& clickEvent);
	virtual ~UIButton();

	DISALLOW_COPY_AND_ASSIGN(UIButton);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** UI ��ư�� �����Դϴ�. */
	enum class EButtonState : int32_t
	{
		DISABLED = 0x00,
		ENABLED  = 0x01,
		PRESSED  = 0x02,
		RELEASED = 0x03,
	};

	/** UI ��ư�� ���� ������Ƽ�� �ʱ�ȭ�մϴ�. */
	void InitProperties(const std::string& buttonPath);

	/** �Է� ���¿� ���� ��ư�� ���¸� ����ϴ�. */
	EButtonState GetButtonState(const EPress& press, const EButtonState& state);

	/** ���콺 Ŀ���� �����Ǵ��� Ȯ���մϴ�. */
	bool IsDetectMouseCursor();

private:
	/** UI ��ư�� �Է� �� �������� ������ �� UI ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** UI ��ư�� �ؽ�Ʈ�� �������� �� ������ ��Ʈ�Դϴ�. */
	TTFont* font_ = nullptr;
	
	/** UI ��ư�� ������ ���콺 ��ư�� �����Դϴ�. */
	EMouse mouse_ = EMouse::LEFT;

	/** UI ��ư�� �����Դϴ�. */
	EButtonState state_ = EButtonState::DISABLED;

	/** UI ��ư Ŭ�� �� ������ �̺�Ʈ�Դϴ�. */
	std::function<void()> clickEvent_ = nullptr;

	/** UI ��ư�� ��׶��� ũ���Դϴ�. */
	Rect2D background_;

	/** UI ��ư�� ǥ���� �ؽ�Ʈ�Դϴ�. */
	std::wstring text_;
	
	/** UI ��ư�� ǥ���� �ؽ�Ʈ�� �����Դϴ�. */
	glm::vec4 textColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	/** UI ��ư�� ���� �� �����Դϴ�. */
	std::map<EButtonState, glm::vec4> stateColors_;
};