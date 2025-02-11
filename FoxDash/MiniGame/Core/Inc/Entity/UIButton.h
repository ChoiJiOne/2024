#pragma once

#include <functional>
#include <map>
#include <string>

#include "Entity/IEntity2D.h"
#include "GLFW/GLFWManager.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class TTFont;
class UICamera;

/** UI 버튼입니다. */
class UIButton : public IEntity2D
{
public:
	/** UI 버튼의 내부 속성을 설정하기 위해서는 Json 포멧의 파일이 필요합니다. */
	UIButton(const std::string& buttonPath, UICamera* uiCamera, TTFont* font, const EMouse& mouse, const std::function<void()>& clickEvent);
	virtual ~UIButton();

	DISALLOW_COPY_AND_ASSIGN(UIButton);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** UI 버튼의 상태입니다. */
	enum class EButtonState : int32_t
	{
		DISABLED = 0x00,
		ENABLED  = 0x01,
		PRESSED  = 0x02,
		RELEASED = 0x03,
	};

	/** UI 버튼의 내부 프로퍼티를 초기화합니다. */
	void InitProperties(const std::string& buttonPath);

	/** 입력 상태에 따른 버튼의 상태를 얻습니다. */
	EButtonState GetButtonState(const EPress& press, const EButtonState& state);

	/** 마우스 커서가 감지되는지 확인합니다. */
	bool IsDetectMouseCursor();

private:
	/** UI 버튼의 입력 및 렌더링에 기준이 될 UI 카메라입니다. */
	UICamera* uiCamera_ = nullptr;

	/** UI 버튼에 텍스트를 렌더링할 때 참조할 폰트입니다. */
	TTFont* font_ = nullptr;
	
	/** UI 버튼이 반응할 마우스 버튼의 종류입니다. */
	EMouse mouse_ = EMouse::LEFT;

	/** UI 버튼의 상태입니다. */
	EButtonState state_ = EButtonState::DISABLED;

	/** UI 버튼 클릭 시 수행할 이벤트입니다. */
	std::function<void()> clickEvent_ = nullptr;

	/** UI 버튼의 백그라운드 크기입니다. */
	Rect2D background_;

	/** UI 버튼에 표시할 텍스트입니다. */
	std::wstring text_;
	
	/** UI 버튼에 표시할 텍스트의 색상입니다. */
	glm::vec4 textColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	/** UI 버튼의 상태 별 색상입니다. */
	std::map<EButtonState, glm::vec4> stateColors_;
};