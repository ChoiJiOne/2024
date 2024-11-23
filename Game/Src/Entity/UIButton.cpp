#include "Entity/EntityManager.h"
#include "Entity/UIButton.h"
#include "Entity/UICamera.h"
#include "GL/RenderManager2D.h"
#include "GL/TTFont.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

UIButton::UIButton(UICamera* uiCamera, TTFont* font, const EMouse& mouse, const std::function<void()>& clickEvent)
	: uiCamera_(uiCamera)
	, font_(font)
	, mouse_(mouse)
	, clickEvent_(clickEvent)
{
	tickOrder_ = 2;
	renderOrder_ = 2;

	background_ = Rect2D(glm::vec2(0.0f, 0.0f), glm::vec2(200.0f, 50.0f));
	text_ = L"Hello";
	textColor_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	textOutlineColor_ = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	stateColors_ = 
	{
		{ EButtonState::DISABLED, glm::vec4(0.0f, 0.0f, 0.0f, 0.2f) },
		{ EButtonState::ENABLED,  glm::vec4(0.0f, 0.0f, 0.0f, 0.6f) },
		{ EButtonState::PRESSED,  glm::vec4(0.0f, 0.0f, 0.0f, 0.9f) },
		{ EButtonState::RELEASED, glm::vec4(0.0f, 0.0f, 0.0f, 0.5f) },
	};

	bIsInitialized_ = true;
}

UIButton::~UIButton()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UIButton::Tick(float deltaSeconds)
{
	EPress press = GLFWManager::GetRef().GetMousePress(mouse_);
	state_ = GetButtonState(press, state_);

	if (state_ == EButtonState::RELEASED && clickEvent_)
	{
		clickEvent_();
	}
}

void UIButton::Render()
{
	renderManager_->DrawRectWireframe(
		background_.center, 
		background_.size.x, 
		background_.size.y, 
		stateColors_.at(state_),
		0.0f
	);

}

void UIButton::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;
	uiCamera_ = nullptr;

	bIsInitialized_ = false;
}

UIButton::EButtonState UIButton::GetButtonState(const EPress& press, const EButtonState& state)
{
	if (!IsDetectMouseCursor())
	{
		if (state == EButtonState::PRESSED && press == EPress::HELD)
		{
			return EButtonState::PRESSED;
		}
		else
		{
			return EButtonState::DISABLED;
		}
	}

	if (state == EButtonState::DISABLED)
	{
		if (press == EPress::HELD || press == EPress::PRESSED)
		{
			return EButtonState::DISABLED;
		}
		else // press == EPress::NONE || press == EPress::RELEASED
		{
			return EButtonState::ENABLED;
		}
	}
	else if (state == EButtonState::ENABLED)
	{
		if (press == EPress::HELD || press == EPress::PRESSED)
		{
			return EButtonState::PRESSED;
		}
		else
		{
			return EButtonState::ENABLED;
		}
	}
	else if (state == EButtonState::PRESSED)
	{
		if (press == EPress::RELEASED)
		{
			return EButtonState::RELEASED;
		}
		else if (press == EPress::HELD || press == EPress::PRESSED)
		{
			return EButtonState::PRESSED;
		}
		else // press == EPress::NONE
		{
			return EButtonState::ENABLED;
		}
	}
	else // state == EButtonState::RELEASED
	{
		if (press == EPress::NONE || press == EPress::RELEASED)
		{
			return EButtonState::ENABLED;
		}
		else // press == EPress::HELD || press == EPress::PRESSED
		{
			return EButtonState::PRESSED;
		}
	}

	return EButtonState::DISABLED;
}

bool UIButton::IsDetectMouseCursor()
{
	return background_.Intersect(uiCamera_->GetMousePointer());
}
