#include "CrossFadeController.h"
#include "Pose.h"

CrossFadeController::CrossFadeController(const Skeleton& skeleton)
{
	SetSkeleton(skeleton);
}

void CrossFadeController::SetSkeleton(const Skeleton& skeleton)
{
	skeleton_ = skeleton;
	pose_ = skeleton_.GetRestPose();
	bWasSetSkeleton_ = true;
}

void CrossFadeController::Play(Clip* target)
{
	targets_.clear();

	clip_ = target;
	pose_ = skeleton_.GetRestPose();
	time_ = target->GetStartTime();
}

void CrossFadeController::FadeTo(Clip* target, float fadeTime)
{
	if (clip_ == nullptr)
	{
		Play(target);
		return;
	}

	if (targets_.size() >= 1)
	{
		if (targets_.back().GetClip() == target)
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

	targets_.push_back(CrossFadeTarget(target, skeleton_.GetRestPose(), fadeTime));
}
