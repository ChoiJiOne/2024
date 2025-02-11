#include "GL/GLAssertion.h"
#include "GL/SpriteAnimator2D.h"
#include "GL/TextureAtlas2D.h"
#include "Utils/Assertion.h"

SpriteAnimator2D::SpriteAnimator2D(TextureAtlas2D* textureAtlas, std::vector<std::string>& names, float animationTime, bool bIsDuration)
	: textureAtlas_(textureAtlas)
	, animationClips_(names.size())
	, animationTime_(animationTime)
	, bIsDuration_(bIsDuration)
{
	for (uint32_t index = 0; index < animationClips_.size(); ++index)
	{
		float startRate = (static_cast<float>(index + 0) / static_cast<float>(animationClips_.size() + 1));
		float endRate = (static_cast<float>(index + 1) / static_cast<float>(animationClips_.size() + 1));

		animationClips_[index].name = names[index];
		animationClips_[index].startTime = animationTime * startRate;
		animationClips_[index].endTime = animationTime * endRate;
	}

	bIsInitialized_ = true;
}

SpriteAnimator2D::~SpriteAnimator2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void SpriteAnimator2D::Release()
{
	CHECK(bIsInitialized_);

	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}

void SpriteAnimator2D::Update(float deltaSeconds)
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

	for (uint32_t index = 0; index < animationClips_.size(); ++index)
	{
		if (animationClips_[index].startTime <= time_ && time_ <= animationClips_[index].endTime)
		{
			currentClipIndex_ = index;
			break;
		}
	}
}

void SpriteAnimator2D::Reset()
{
	time_ = 0.0f;
	currentClipIndex_ = 0;
}