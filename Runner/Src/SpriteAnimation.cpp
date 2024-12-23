#include "Assertion.h"
#include "Atlas2D.h"

#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(Atlas2D* atlas, const std::vector<std::string>& clipNames, bool bIsDuration, float animationTime)
	: bIsDuration_(bIsDuration)
	, animationTime_(animationTime)
	, clips_(clipNames.size() + 1)
{
	for (uint32_t index = 0; index < clips_.size() - 1; ++index)
	{
		float rate = static_cast<float>(index) / static_cast<float>(clips_.size());

		clips_[index].first = clipNames[index];
		clips_[index].second = animationTime_ * rate;
	}

	clips_.back().first = clips_.front().first;
	clips_.back().second = animationTime_;

	bIsInitialized_ = true;
}

SpriteAnimation::~SpriteAnimation()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void SpriteAnimation::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}

void SpriteAnimation::Update(float deltaSeconds)
{
	time_ += deltaSeconds;
	if (time_ >= animationTime_)
	{
		if (bIsDuration_)
		{
			time_ -= animationTime_;
		}
		else
		{
			time_ = animationTime_;
			return;
		}
	}

	for (uint32_t index = 0; index < clips_.size() - 1; ++index)
	{
		if (clips_[index].second <= time_ && time_ <= clips_[index + 1].second)
		{
			currentIndex_ = index;
			break;
		}
	}

	if (!clips_.empty())
	{
		time_ = GameMath::Clamp<float>(time_, clips_.front().second, clips_.back().second);
	}
}

void SpriteAnimation::Reset()
{
	currentIndex_ = 0;
	time_ = 0.0f;
}
