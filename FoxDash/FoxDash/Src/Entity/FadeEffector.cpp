#include "Entity/EntityManager.h"
#include "Entity/FadeEffector.h"
#include "Utils/Assertion.h"

FadeEffector::FadeEffector()
{
	bIsInitialized_ = true;
}

FadeEffector::~FadeEffector()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void FadeEffector::Tick(float deltaSeconds)
{
	if (state_ != EState::PROGRESS)
	{
		return;
	}

	float bias = (type_ == EType::FADE_IN) ? -1.0f : 1.0f;
	effectTime_ += deltaSeconds * bias;
	effectTime_ = glm::clamp<float>(effectTime_, 0.0f, maxEffectTime_);

	factor_ = effectTime_ / maxEffectTime_;
	if (factor_ <= 0.0f || factor_ >= 1.0f)
	{
		type_ = EType::NONE;
		state_ = EState::DONE;
	}
}

void FadeEffector::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}

// factor 값이 1.0 => 0.0
void FadeEffector::StartIn(float time)
{
	state_ = EState::PROGRESS;
	type_ = EType::FADE_IN;
	effectTime_ = time;
	maxEffectTime_ = time;
}

// factor 값이 0.0 => 1.0
void FadeEffector::StartOut(float time)
{
	state_ = EState::PROGRESS;
	type_ = EType::FADE_OUT;
	effectTime_ = 0.0f;
	maxEffectTime_ = time;
}

void FadeEffector::Reset()
{
	state_ = EState::WAIT;
	type_ = EType::NONE;
}
