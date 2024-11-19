#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/constants.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/norm.hpp>

#include "Entity/EntityManager.h"
#include "Entity/UIBar.h"
#include "Entity/Player.h"
#include "GL/TTFont.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

UIBar::UIBar(UICamera* uiCamera, TTFont* font)
	: uiCamera_(uiCamera)
	, font_(font)
{
	tickOrder_ = 1;
	renderOrder_ = 1;

	background_ = Rect2D(glm::vec2(0.0f, -300.0f), glm::vec2(400.0f, 25.0f));
	barBound_ = background_;
	backgroundColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	barColor_ = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	bar_ = 200.0f;
	barMark_ = bar_;
	minBar_ = 0.0f;
	maxBar_ = bar_;
	barSlideSpeed_ = 50.0f;
	
	text_ = PrintF(L"%3d / %3d", static_cast<int32_t>(barMark_), static_cast<int32_t>(maxBar_));

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
	renderManager_->DrawString(font_, text_, basePos, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void UIBar::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;
	uiCamera_ = nullptr;

	bIsInitialized_ = false;
}

void UIBar::SetBar(float bar)
{
	bar_ = bar;
	bar_ = glm::clamp<float>(bar_, 0.0f, maxBar_);
}
