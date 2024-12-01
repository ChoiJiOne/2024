#include <json/json.h>

#include "Entity/UIButton.h"
#include "Entity/UICamera.h"
#include "GL/RenderManager2D.h"
#include "GL/TTFont.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

UIButton::UIButton(const std::string& buttonPath, UICamera* uiCamera, TTFont* font, const EMouse& mouse, const std::function<void()>& clickEvent)
	: uiCamera_(uiCamera)
	, font_(font)
	, mouse_(mouse)
	, clickEvent_(clickEvent)
{
	InitProperties(buttonPath);
	
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
	renderManager_->DrawRect(background_.center, background_.size.x, background_.size.y, stateColors_.at(state_), 0.0f);

	glm::vec2 basePos = font_->MeasureBasePos(text_, background_.center);
	renderManager_->DrawString(font_, text_, basePos, textColor_);
}

void UIButton::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;
	uiCamera_ = nullptr;

	bIsInitialized_ = false;
}

void UIButton::InitProperties(const std::string& buttonPath)
{
	std::vector<uint8_t> buffer;
	std::string errMsg;
	ASSERTION(ReadFile(buttonPath, buffer, errMsg), "%s", errMsg.c_str());

	std::string jsonString(buffer.begin(), buffer.end());
	Json::Value root;
	Json::Reader reader;
	ASSERTION(reader.parse(jsonString, root), "Failed to parse '%s' file.", buttonPath.c_str());

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

	CHECK(root["Text"].isString() && !root["Text"].isNull());
	text_ = ConvertString(root["Text"].asString());

	CHECK(root["TextColor"].isObject() && !root["TextColor"].isNull());
	const Json::Value& textColor = root["TextColor"];
	CHECK(textColor["r"].isDouble() && !textColor["r"].isNull());
	CHECK(textColor["g"].isDouble() && !textColor["g"].isNull());
	CHECK(textColor["b"].isDouble() && !textColor["b"].isNull());
	CHECK(textColor["a"].isDouble() && !textColor["a"].isNull());
	textColor_.x = textColor["r"].asFloat();
	textColor_.y = textColor["g"].asFloat();
	textColor_.z = textColor["b"].asFloat();
	textColor_.w = textColor["a"].asFloat();

	CHECK(root["DisabledColor"].isObject() && !root["DisabledColor"].isNull());
	const Json::Value& disabledColor = root["DisabledColor"];
	CHECK(disabledColor["r"].isDouble() && !disabledColor["r"].isNull());
	CHECK(disabledColor["g"].isDouble() && !disabledColor["g"].isNull());
	CHECK(disabledColor["b"].isDouble() && !disabledColor["b"].isNull());
	CHECK(disabledColor["a"].isDouble() && !disabledColor["a"].isNull());
	stateColors_.insert({ EButtonState::DISABLED, glm::vec4(disabledColor["r"].asFloat(), disabledColor["g"].asFloat(), disabledColor["b"].asFloat(), disabledColor["a"].asFloat()) });

	CHECK(root["EnabledColor"].isObject() && !root["EnabledColor"].isNull());
	const Json::Value& enabledColor = root["EnabledColor"];
	CHECK(enabledColor["r"].isDouble() && !enabledColor["r"].isNull());
	CHECK(enabledColor["g"].isDouble() && !enabledColor["g"].isNull());
	CHECK(enabledColor["b"].isDouble() && !enabledColor["b"].isNull());
	CHECK(enabledColor["a"].isDouble() && !enabledColor["a"].isNull());
	stateColors_.insert({ EButtonState::ENABLED, glm::vec4(enabledColor["r"].asFloat(), enabledColor["g"].asFloat(), enabledColor["b"].asFloat(), enabledColor["a"].asFloat()) });
	
	CHECK(root["PressedColor"].isObject() && !root["PressedColor"].isNull());
	const Json::Value& pressedColor = root["PressedColor"];
	CHECK(pressedColor["r"].isDouble() && !pressedColor["r"].isNull());
	CHECK(pressedColor["g"].isDouble() && !pressedColor["g"].isNull());
	CHECK(pressedColor["b"].isDouble() && !pressedColor["b"].isNull());
	CHECK(pressedColor["a"].isDouble() && !pressedColor["a"].isNull());
	stateColors_.insert({ EButtonState::PRESSED, glm::vec4(pressedColor["r"].asFloat(), pressedColor["g"].asFloat(), pressedColor["b"].asFloat(), pressedColor["a"].asFloat()) });
	
	CHECK(root["ReleasedColor"].isObject() && !root["ReleasedColor"].isNull());
	const Json::Value& releasedColor = root["ReleasedColor"];
	CHECK(releasedColor["r"].isDouble() && !releasedColor["r"].isNull());
	CHECK(releasedColor["g"].isDouble() && !releasedColor["g"].isNull());
	CHECK(releasedColor["b"].isDouble() && !releasedColor["b"].isNull());
	CHECK(releasedColor["a"].isDouble() && !releasedColor["a"].isNull());
	stateColors_.insert({ EButtonState::RELEASED, glm::vec4(releasedColor["r"].asFloat(), releasedColor["g"].asFloat(), releasedColor["b"].asFloat(), releasedColor["a"].asFloat()) });
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
