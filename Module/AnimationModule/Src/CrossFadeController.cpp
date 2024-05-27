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
