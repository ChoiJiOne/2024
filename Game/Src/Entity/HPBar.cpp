#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/constants.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/norm.hpp>

#include "Entity/EntityManager.h"
#include "Entity/HPBar.h"
#include "Entity/Player.h"
#include "Utils/Assertion.h"

HPBar::HPBar(UICamera* uiCamera)
	: uiCamera_(uiCamera)
{
	tickOrder_ = 1;
	renderOrder_ = 1;

	background_ = Rect2D(glm::vec2(0.0f, -300.0f), glm::vec2(400.0f, 20.0f));
	hpBound_ = background_;
	backgroundColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	hpColor_ = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	hp_ = 200.0f;
	hpMark_ = hp_;
	minHp_ = 0.0f;
	maxHp_ = hp_;
	hpSpeed_ = 50.0f;

	bIsInitialized_ = true;
}

HPBar::~HPBar()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void HPBar::Tick(float deltaSeconds)
{
	if (glm::epsilonEqual<float>(glm::abs(hp_ - hpMark_), 0.0f, glm::epsilon<float>()))
	{
		return;
	}

	if (hpMark_ > hp_)
	{
		hpMark_ -= deltaSeconds * hpSpeed_;
		hpMark_ = glm::clamp<float>(hpMark_, hp_, maxHp_);
	}
	else
	{
		hpMark_ += deltaSeconds * hpSpeed_;
		hpMark_ = glm::clamp<float>(hpMark_, 0.0f, maxHp_);
	}

	hpBound_.center = background_.center + glm::vec2(-background_.size.x * 0.5f, +background_.size.y * 0.5f);
	hpBound_.size.x = background_.size.x * (hpMark_ / maxHp_);
	hpBound_.center += glm::vec2(hpBound_.size.x * 0.5f, -hpBound_.size.y * 0.5f);
}

void HPBar::Render()
{
	renderManager_->DrawRect(background_.center, background_.size.x, background_.size.y, backgroundColor_, 0.0f);
	renderManager_->DrawRect(hpBound_.center, hpBound_.size.x, hpBound_.size.y, hpColor_, 0.0f);
}

void HPBar::Release()
{
	CHECK(bIsInitialized_);

	uiCamera_ = nullptr;

	bIsInitialized_ = false;
}

void HPBar::SetHP(float hp)
{
	hp_ = hp;
	hp_ = glm::clamp<float>(hp_, 0.0f, maxHp_);
}
