#pragma once

#include <functional>
#include <map>

#include "Entity/IEntity2D.h"
#include "GLFW/GLFWManager.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class UICamera;

/** UI �����̴� ��ƼƼ�Դϴ�. */
class UISlider : public IEntity2D
{
public:
	/** UI �����̴��� ���� �Ӽ��� �����ϱ� ���ؼ��� Json ������ ������ �ʿ��մϴ�. */
	UISlider(const std::string& sliderPath, UICamera* uiCamera, const EMouse& mouse, const std::function<void(float)>& moveSliderEvent);
	virtual ~UISlider();

	DISALLOW_COPY_AND_ASSIGN(UISlider);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** UI �����̴��� �����Դϴ�. */
	enum class EState : int32_t
	{
		DISABLED = 0x00,
		ENABLED  = 0x01,
		PRESSED  = 0x02,
		RELEASED = 0x03,
	};

	/** UI �����̴��� ���� ������Ƽ�� �ʱ�ȭ�մϴ�. */
	void InitProperties(const std::string& sliderPath);

	/** �Է� ���¿� ���� ���¸� ����ϴ�. */
	EState GetState(const EPress& press, const EState& state);

	/** ���콺 Ŀ���� �����Ǵ��� Ȯ���մϴ�. */
	bool IsDetectMouseCursor();

private:
	/** UI �����̴��� �Է� ó���� ����� UI ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** UI �����̴��� ��׶��� ��ġ �� ũ���Դϴ�. */
	Rect2D background_;

	/** UI �����̴��� ������ ���콺 ��ư�� �����Դϴ�. */
	EMouse mouse_ = EMouse::LEFT;

	/** UI �����̴��� ���� �����Դϴ�. */
	EState state_ = EState::DISABLED;

	/** UI �����̴��� ���� �� �����Դϴ�. */
	std::map<EState, glm::vec4> stateColors_;

	/** UI �����̴��� ��ġ �� ũ���Դϴ�. */
	Rect2D slider_;

	/** UI �����̴��� �ּ� X��ǥ ���Դϴ�. */
	float sliderMinX_ = 0.0f;

	/** UI �����̴��� �ִ� X��ǥ ���Դϴ�. */
	float sliderMaxX_ = 0.0f;

	/** UI �����̴��� X��ǥ ���Դϴ�. */
	float sliderX_ = 0.0f;

	/** UI �����̴��� �����Դϴ�. */
	glm::vec4 sliderColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	/** UI �����̴��� ������ ���� �� ������ �̺�Ʈ�Դϴ�. */
	std::function<void(float)> moveSliderEvent_ = nullptr;
};