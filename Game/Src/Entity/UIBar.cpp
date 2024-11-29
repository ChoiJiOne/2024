#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/constants.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/norm.hpp>

#include <json/json.h>

#include "Entity/EntityManager.h"
#include "Entity/UIBar.h"
#include "Entity/Player.h"
#include "GL/TTFont.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

UIBar::UIBar(const std::string& barPath, TTFont* font)
	: font_(font)
{
	InitProperties(barPath);
	
	text_ = PrintF(L"%3d / %3d", static_cast<int32_t>(barMark_), static_cast<int32_t>(maxBar_));

	barBound_ = background_;
	barBound_.center = background_.center + glm::vec2(-background_.size.x * 0.5f, +background_.size.y * 0.5f);
	barBound_.size.x = background_.size.x * (barMark_ / maxBar_);
	barBound_.center += glm::vec2(barBound_.size.x * 0.5f, -barBound_.size.y * 0.5f);

	bIsInitialized_ = true;
}

UIBar::~UIBar()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UIBar::Tick(float deltaSeconds)
{
	if (glm::epsilonEqual<float>(glm::abs(bar_ - barMark_), 0.0f, glm::epsilon<float>()))
	{
		return;
	}

	if (barMark_ > bar_)
	{
		barMark_ -= deltaSeconds * barSlideSpeed_;
		barMark_ = glm::clamp<float>(barMark_, bar_, maxBar_);
	}
	else
	{
		barMark_ += deltaSeconds * barSlideSpeed_;
		barMark_ = glm::clamp<float>(barMark_, 0.0f, maxBar_);
	}

	barBound_.center = background_.center + glm::vec2(-background_.size.x * 0.5f, +background_.size.y * 0.5f);
	barBound_.size.x = background_.size.x * (barMark_ / maxBar_);
	barBound_.center += glm::vec2(barBound_.size.x * 0.5f, -barBound_.size.y * 0.5f);
	
	text_ = PrintF(L"%3d / %3d", static_cast<int32_t>(barMark_), static_cast<int32_t>(maxBar_));
}

void UIBar::Render()
{
	renderManager_->DrawRect(background_.center, background_.size.x, background_.size.y, backgroundColor_, 0.0f);
	renderManager_->DrawRect(barBound_.center, barBound_.size.x, barBound_.size.y, barColor_, 0.0f);

	glm::vec2 basePos = font_->MeasureBasePos(text_, background_.center);
	renderManager_->DrawString(font_, text_, basePos, textColor_);
}

void UIBar::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;

	bIsInitialized_ = false;
}

void UIBar::SetBar(float bar)
{
	bar_ = bar;
	bar_ = glm::clamp<float>(bar_, 0.0f, maxBar_);
}

void UIBar::SetMaxBar(float maxBar)
{
	maxBar_ = maxBar;

	barBound_.center = background_.center + glm::vec2(-background_.size.x * 0.5f, +background_.size.y * 0.5f);
	barBound_.size.x = background_.size.x * (barMark_ / maxBar_);
	barBound_.center += glm::vec2(barBound_.size.x * 0.5f, -barBound_.size.y * 0.5f);

	text_ = PrintF(L"%3d / %3d", static_cast<int32_t>(barMark_), static_cast<int32_t>(maxBar_));
}

void UIBar::InitProperties(const std::string& barPath)
{
	std::vector<uint8_t> buffer;
	std::string errMsg;
	ASSERTION(ReadFile(barPath, buffer, errMsg), "%s", errMsg.c_str());

	std::string jsonString(buffer.begin(), buffer.end());
	Json::Value root;
	Json::Reader reader;
	ASSERTION(reader.parse(jsonString, root), "Failed to parse '%s' file.", barPath.c_str());

	CHECK(root["Background"].isObject() && !root["Background"].isNull());
	const Json::Value& background = root["Background"];

	CHECK(background["Bound"].isObject() && !background["Bound"].isNull());
	const Json::Value& backgroundBound = background["Bound"];

	CHECK(backgroundBound["x"].isDouble() && !backgroundBound["x"].isNull());
	CHECK(backgroundBound["y"].isDouble() && !backgroundBound["y"].isNull());
	CHECK(backgroundBound["w"].isDouble() && !backgroundBound["w"].isNull());
	CHECK(backgroundBound["h"].isDouble() && !backgroundBound["h"].isNull());
	background_.center.x = backgroundBound["x"].asFloat();
	background_.center.y = backgroundBound["y"].asFloat();
	background_.size.x = backgroundBound["w"].asFloat();
	background_.size.y = backgroundBound["h"].asFloat();

	CHECK(background["Color"].isObject() && !background["Color"].isNull());
	const Json::Value& backgroundColor = background["Color"];

	CHECK(backgroundColor["r"].isDouble() && !backgroundColor["r"].isNull());
	CHECK(backgroundColor["g"].isDouble() && !backgroundColor["g"].isNull());
	CHECK(backgroundColor["b"].isDouble() && !backgroundColor["b"].isNull());
	CHECK(backgroundColor["a"].isDouble() && !backgroundColor["a"].isNull());
	backgroundColor_.x = backgroundColor["r"].asFloat();
	backgroundColor_.y = backgroundColor["g"].asFloat();
	backgroundColor_.z = backgroundColor["b"].asFloat();
	backgroundColor_.w = backgroundColor["a"].asFloat();

	CHECK(root["Bar"].isObject() && !root["Bar"].isNull());
	const Json::Value& bar = root["Bar"];

	CHECK(bar["Size"].isDouble() && !bar["Size"].isNull());
	CHECK(bar["SlideSpeed"].isDouble() && !bar["SlideSpeed"].isNull());
	CHECK(bar["IsFullFill"].isBool() && !bar["IsFullFill"].isNull());

	maxBar_ = bar["Size"].asFloat();
	bar_ = bar["IsFullFill"].asBool() ? maxBar_ : 0.0f;
	barMark_ = bar_;
	barSlideSpeed_ = bar["SlideSpeed"].asFloat();

	CHECK(bar["Color"].isObject() && !bar["Color"].isNull());
	const Json::Value& barColor = bar["Color"];
	barColor_.x = barColor["r"].asFloat();
	barColor_.y = barColor["g"].asFloat();
	barColor_.z = barColor["b"].asFloat();
	barColor_.w = barColor["a"].asFloat();

	CHECK(bar["TextColor"].isObject() && !bar["TextColor"].isNull());
	const Json::Value& textColor = bar["TextColor"];
	textColor_.x = textColor["r"].asFloat();
	textColor_.y = textColor["g"].asFloat();
	textColor_.z = textColor["b"].asFloat();
	textColor_.w = textColor["a"].asFloat();
}
