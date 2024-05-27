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

void CrossFadeController::Play(Clip* clip)
{
	targets_.clear();

	clip_ = clip;
	pose_ = skeleton_.GetRestPose();
	time_ = clip_->GetStartTime();
}