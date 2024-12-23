#pragma once

#include <functional>
#include <map>

#include "Entity/IEntity2D.h"
#include "GLFW/GLFWManager.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class UICamera;

/** UI 슬라이더 엔티티입니다. */
class UISlider : public IEntity2D
{
public:
	/** UI 슬라이더의 내부 속성을 설정하기 위해서는 Json 포멧의 파일이 필요합니다. */
	UISlider(const std::string& sliderPath, UICamera* uiCamera, const EMouse& mouse, const std::function<void(float)>& moveSliderEvent);
	virtual ~UISlider();

	DISALLOW_COPY_AND_ASSIGN(UISlider);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** UI 슬라이더의 상태입니다. */
	enum class EState : int32_t
	{
		DISABLED = 0x00,
		ENABLED  = 0x01,
		PRESSED  = 0x02,
		RELEASED = 0x03,
	};

	/** UI 슬라이더의 내부 프로퍼티를 초기화합니다. */
	void InitProperties(const std::string& sliderPath);

	/** 입력 상태에 따른 상태를 얻습니다. */
	EState GetState(const EPress& press, const EState& state);

	/** 마우스 커서가 감지되는지 확인합니다. */
	bool IsDetectMouseCursor();

private:
	/** UI 슬라이더의 입력 처리에 사용할 UI 카메라입니다. */
	UICamera* uiCamera_ = nullptr;

	/** UI 슬라이더의 백그라운드 위치 및 크기입니다. */
	Rect2D background_;

	/** UI 슬라이더가 반응할 마우스 버튼의 종류입니다. */
	EMouse mouse_ = EMouse::LEFT;

	/** UI 슬라이더의 현재 상태입니다. */
	EState state_ = EState::DISABLED;

	/** UI 슬라이더의 상태 별 색상입니다. */
	std::map<EState, glm::vec4> stateColors_;

	/** UI 슬라이더의 위치 및 크기입니다. */
	Rect2D slider_;

	/** UI 슬라이더의 최소 X좌표 값입니다. */
	float sliderMinX_ = 0.0f;

	/** UI 슬라이더의 최대 X좌표 값입니다. */
	float sliderMaxX_ = 0.0f;

	/** UI 슬라이더의 X좌표 값입니다. */
	float sliderX_ = 0.0f;

	/** UI 슬라이더의 색상입니다. */
	glm::vec4 sliderColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	/** UI 슬라이더의 움직임 감지 시 실행할 이벤트입니다. */
	std::function<void(float)> moveSliderEvent_ = nullptr;
};