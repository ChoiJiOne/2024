#include "CrossFadeController.h"

void CrossFadeContoller::Play(Clip* target)
{
	targets_.clear();
	clip_ = target;
	pose_ = skeleton_.GetRestPose();
	time_ = target->GetStartTime();
}

void CrossFadeContoller::FadeTo(Clip* target, float fadeSeconds)
{
	if (clip_ == nullptr)
	{
		Play(target);
		return;
	}

	if (targets_.size() >= 1)
	{
		if (targets_.back().clip == target)
		{
			return;
		}
	}
	else
	{
		if (clip_ == target)
		{
			return;
		}
	}

	targets_.push_back(CrossFadeTarget{ skeleton_.GetRestPose(), target, target->GetStartTime(), fadeSeconds, 0.0f });
}

void CrossFadeContoller::Update(float deltaSeconds)
{
	if (clip_ == nullptr) return;

	for (uint32_t index = 0; index < targets_.size(); ++index)
	{
		if (targets_[index].elapsed >= targets_[index].duration)
		{
			clip_ = targets_[index].clip;
			time_ = targets_[index].time;
			pose_ = targets_[index].pose;

			targets_.erase(targets_.begin() + index);
			break;
		}
	}

	pose_ = skeleton_.GetRestPose();
	time_ = clip_->Sample(pose_, time_ + deltaSeconds);

	for (uint32_t index = 0; index < targets_.size(); ++index)
	{
		CrossFadeTarget& target = targets_[index];
		target.time = target.clip->Sample(target.pose, target.time + deltaSeconds);
		target.elapsed += deltaSeconds;

		float t = target.elapsed / target.duration;
		if (t > 1.0f)
		{
			t = 1.0f;
		}

		Pose::Blend(pose_, pose_, target.pose, t, -1);
	}
}