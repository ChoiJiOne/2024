#include <json/json.h>

#include "Entity/UIText.h"
#include "GL/GLManager.h"
#include "GL/TTFont.h"
#include "Utils/Assertion.h"

UIText::UIText(const std::string& textPath, TTFont* font)
	: font_(font)
{
	InitProperties(textPath);

	bIsInitialized_ = true;
}

UIText::~UIText()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UIText::Tick(float deltaSeconds)
{
}

void UIText::Render()
{
	glm::vec2 basePos = font_->MeasureBasePos(text_, centerPos_);
	renderManager_->DrawString(font_, text_, basePos, textColor_, outlineColor_);
}

void UIText::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;

	bIsInitialized_ = false;
}

void UIText::InitProperties(const std::string& textPath)
{
	std::vector<uint8_t> buffer;
	std::string errMsg;
	ASSERTION(ReadFile(textPath, buffer, errMsg), "%s", errMsg.c_str());

	std::string jsonString(buffer.begin(), buffer.end());
	Json::Value root;
	Json::Reader reader;
	ASSERTION(reader.parse(jsonString, root), "Failed to parse '%s' file.", textPath.c_str());

	CHECK(root["Text"].isString() && !root["Text"].isNull());
	text_ = ConvertString(root["Text"].asString());

	CHECK(root["CenterPos"].isObject() && !root["CenterPos"].isNull());
	const Json::Value& centerPos = root["CenterPos"];

	CHECK(centerPos["x"].isDouble() && !centerPos["x"].isNull());
	CHECK(centerPos["y"].isDouble() && !centerPos["y"].isNull());
	centerPos_.x = centerPos["x"].asFloat();
	centerPos_.y = centerPos["y"].asFloat();

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

	CHECK(root["OutlineColor"].isObject() && !root["OutlineColor"].isNull());
	const Json::Value& outlineColor = root["OutlineColor"];

	CHECK(outlineColor["r"].isDouble() && !outlineColor["r"].isNull());
	CHECK(outlineColor["g"].isDouble() && !outlineColor["g"].isNull());
	CHECK(outlineColor["b"].isDouble() && !outlineColor["b"].isNull());
	CHECK(outlineColor["a"].isDouble() && !outlineColor["a"].isNull());
	outlineColor_.x = outlineColor["r"].asFloat();
	outlineColor_.y = outlineColor["g"].asFloat();
	outlineColor_.z = outlineColor["b"].asFloat();
	outlineColor_.w = outlineColor["a"].asFloat();
}
