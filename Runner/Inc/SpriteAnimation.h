#pragma once

#include <string>
#include <vector>

#include "IResource.h"

class Atlas2D;

class SpriteAnimation : public IResource
{
public:
	SpriteAnimation(Atlas2D* atlas, const std::vector<std::string>& clipNames, bool bIsDuration, float animationTime);
	virtual ~SpriteAnimation();

	DISALLOW_COPY_AND_ASSIGN(SpriteAnimation);

	virtual void Release() override;

	void Update(float deltaSeconds);

	const std::string& GetCurrentClip() const { return clips_.at(currentIndex_).first; }

	bool IsDuration() const { return bIsDuration_; }
	float GetTime() const { return time_; }
	float GetAnimationTime() const { return animationTime_; }

	void Reset();

private:
	Atlas2D* atlas_ = nullptr;

	std::vector<std::pair<std::string, float>> clips_;

	uint32_t currentIndex_ = 0;
	bool bIsDuration_ = false;
	float time_ = 0.0f;
	float animationTime_ = 0.0f;
};