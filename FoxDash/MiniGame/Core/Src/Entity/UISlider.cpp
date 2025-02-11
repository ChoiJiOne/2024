#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/constants.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/norm.hpp>

#include <json/json.h>

#include "Entity/UICamera.h"
#include "Entity/UISlider.h"
#include "GL/RenderManager2D.h"
#include "Utils/Assertion.h"

UISlider::UISlider(const std::string& sliderPath, UICamera* uiCamera, const EMouse& mouse, const std::function<void(float)>& moveSliderEvent)
	: uiCamera_(uiCamera)
	, mouse_(mouse)
	, moveSliderEvent_(moveSliderEvent)
{
	InitProperties(sliderPath);

	bIsInitialized_ = true;
}

UISlider::~UISlider()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UISlider::Tick(float deltaSeconds)
{
	EPress press = GLFWManager::GetRef().GetMousePress(mouse_);
	state_ = GetState(press, state_);
	if (state_ != EState::PRESSED)
	{
		return;
	}

	float sliderX = uiCamera_->GetMousePointer()->center.x;
	sliderX = glm::clamp<float>(sliderX, sliderMinX_, sliderMaxX_);

	if (glm::epsilonNotEqual<float>(sliderX, sliderX_, glm::epsilon<float>()))
	{
		sliderX_ = sliderX;
		slider_.center.x = sliderX_;

		float rate = (sliderX_ - sliderMinX_) / (sliderMaxX_ - sliderMinX_);
		if (moveSliderEvent_)
		{
			moveSliderEvent_(rate);
		}
	}
}

void UISlider::Render()
{
	renderManager_->DrawRect(background_.center, background_.size.x, background_.size.y, stateColors_.at(state_), 0.0f);
	renderManager_->DrawRect(slider_.center, slider_.size.x, slider_.size.y, sliderColor_, 0.0f);
}

void UISlider::Release()
{
	CHECK(bIsInitialized_);

	uiCamera_ = nullptr;

	bIsInitialized_ = false;
}

void UISlider::InitProperties(const std::string& sliderPath)
{
	std::vector<uint8_t> buffer;
	std::string errMsg;
	ASSERTION(ReadFile(sliderPath, buffer, errMsg), "%s", errMsg.c_str());

	std::string jsonString(buffer.begin(), buffer.end());
	Json::Value root;
	Json::Reader reader;
	ASSERTION(reader.parse(jsonString, root), "Failed to parse '%s' file.", sliderPath.c_str());

	CHECK(root["Background"].isObject() && !root["Background"].isNull());
	const Json::Value& background = root["Background"];

	CHECK(background["x"].isDouble() && !background["x"].isNull());
	CHECK(background["y"].isDouble() && !background["y"].isNull());
	CHECK(background["w"].isDouble() && !background["w"].isNull());
	CHECK(background["h"].isDouble() && !background["h"].isNull());
	background_.center.x = background["x"].asFloat();
	background_.center.y = background["y"].asFloat();
	background_.size.x = background["w"].asFloat();
	background_.size.y = background["h"].asFloat();
	
	CHECK(root["DisabledColor"].isObject() && !root["DisabledColor"].isNull());
	const Json::Value& disabledColor = root["DisabledColor"];
	CHECK(disabledColor["r"].isDouble() && !disabledColor["r"].isNull());
	CHECK(disabledColor["g"].isDouble() && !disabledColor["g"].isNull());
	CHECK(disabledColor["b"].isDouble() && !disabledColor["b"].isNull());
	CHECK(disabledColor["a"].isDouble() && !disabledColor["a"].isNull());
	stateColors_.insert({ EState::DISABLED, glm::vec4(disabledColor["r"].asFloat(), disabledColor["g"].asFloat(), disabledColor["b"].asFloat(), disabledColor["a"].asFloat()) });

	CHECK(root["EnabledColor"].isObject() && !root["EnabledColor"].isNull());
	const Json::Value& enabledColor = root["EnabledColor"];
	CHECK(enabledColor["r"].isDouble() && !enabledColor["r"].isNull());
	CHECK(enabledColor["g"].isDouble() && !enabledColor["g"].isNull());
	CHECK(enabledColor["b"].isDouble() && !enabledColor["b"].isNull());
	CHECK(enabledColor["a"].isDouble() && !enabledColor["a"].isNull());
	stateColors_.insert({ EState::ENABLED, glm::vec4(enabledColor["r"].asFloat(), enabledColor["g"].asFloat(), enabledColor["b"].asFloat(), enabledColor["a"].asFloat()) });

	CHECK(root["PressedColor"].isObject() && !root["PressedColor"].isNull());
	const Json::Value& pressedColor = root["PressedColor"];
	CHECK(pressedColor["r"].isDouble() && !pressedColor["r"].isNull());
	CHECK(pressedColor["g"].isDouble() && !pressedColor["g"].isNull());
	CHECK(pressedColor["b"].isDouble() && !pressedColor["b"].isNull());
	CHECK(pressedColor["a"].isDouble() && !pressedColor["a"].isNull());
	stateColors_.insert({ EState::PRESSED, glm::vec4(pressedColor["r"].asFloat(), pressedColor["g"].asFloat(), pressedColor["b"].asFloat(), pressedColor["a"].asFloat()) });

	CHECK(root["ReleasedColor"].isObject() && !root["ReleasedColor"].isNull());
	const Json::Value& releasedColor = root["ReleasedColor"];
	CHECK(releasedColor["r"].isDouble() && !releasedColor["r"].isNull());
	CHECK(releasedColor["g"].isDouble() && !releasedColor["g"].isNull());
	CHECK(releasedColor["b"].isDouble() && !releasedColor["b"].isNull());
	CHECK(releasedColor["a"].isDouble() && !releasedColor["a"].isNull());
	stateColors_.insert({ EState::RELEASED, glm::vec4(releasedColor["r"].asFloat(), releasedColor["g"].asFloat(), releasedColor["b"].asFloat(), releasedColor["a"].asFloat()) });

	CHECK(root["SliderColor"].isObject() && !root["SliderColor"].isNull());
	const Json::Value& sliderColor = root["SliderColor"];
	CHECK(sliderColor["r"].isDouble() && !sliderColor["r"].isNull());
	CHECK(sliderColor["g"].isDouble() && !sliderColor["g"].isNull());
	CHECK(sliderColor["b"].isDouble() && !sliderColor["b"].isNull());
	CHECK(sliderColor["a"].isDouble() && !sliderColor["a"].isNull());
	sliderColor_ = glm::vec4(sliderColor["r"].asFloat(), sliderColor["g"].asFloat(), sliderColor["b"].asFloat(), sliderColor["a"].asFloat());

	CHECK(root["SliderScale"].isDouble() && !root["SliderScale"].isNull());
	float sliderScale = root["SliderScale"].asFloat();

	slider_.size = background_.size;
	slider_.size.x *= sliderScale;

	CHECK(root["SliderXScale"].isDouble() && !root["SliderXScale"].isNull());
	float sliderXScale = root["SliderXScale"].asFloat();

	sliderMinX_ = background_.center.x - (background_.size.x - slider_.size.x) * 0.5f;
	sliderMaxX_ = background_.center.x + (background_.size.x - slider_.size.x) * 0.5f;
	slider_.center = glm::vec2(sliderMinX_ + (sliderMaxX_ - sliderMinX_) * sliderXScale, background_.center.y);
}

UISlider::EState UISlider::GetState(const EPress& press, const EState& state)
{
	if (!IsDetectMouseCursor())
	{
		if (state == EState::PRESSED && press == EPress::HELD)
		{
			return EState::PRESSED;
		}
		else
		{
			return EState::DISABLED;
		}
	}

	if (state == EState::DISABLED)
	{
		if (press == EPress::HELD || press == EPress::PRESSED)
		{
			return EState::DISABLED;
		}
		else // press == EPress::NONE || press == EPress::RELEASED
		{
			return EState::ENABLED;
		}
	}
	else if (state == EState::ENABLED)
	{
		if (press == EPress::HELD || press == EPress::PRESSED)
		{
			return EState::PRESSED;
		}
		else
		{
			return EState::ENABLED;
		}
	}
	else if (state == EState::PRESSED)
	{
		if (press == EPress::RELEASED)
		{
			return EState::RELEASED;
		}
		else if (press == EPress::HELD || press == EPress::PRESSED)
		{
			return EState::PRESSED;
		}
		else // press == EPress::NONE
		{
			return EState::ENABLED;
		}
	}
	else // state == EState::RELEASED
	{
		if (press == EPress::NONE || press == EPress::RELEASED)
		{
			return EState::ENABLED;
		}
		else // press == EPress::HELD || press == EPress::PRESSED
		{
			return EState::PRESSED;
		}
	}

	return EState::DISABLED;
}

bool UISlider::IsDetectMouseCursor()
{
	return background_.Intersect(uiCamera_->GetMousePointer());
}
