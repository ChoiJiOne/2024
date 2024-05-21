#include "Assertion.h"
#include "Skeleton.h"

void Skeleton::SetProperties(const Pose& restPose, const Pose& bindPose, const std::vector<std::string>& jointNames)
{
	restPose_ = restPose;
	bindPose_ = bindPose;
	jointNames_ = jointNames;
	UpdateInverseBindPose();
}

const std::string& Skeleton::GetJointName(uint32_t index) const
{
	CHECK(0 <= index && index < jointNames_.size());
	return jointNames_[index];
}

std::string& Skeleton::GetJointName(uint32_t index)
{
	CHECK(0 <= index && index < jointNames_.size());
	return jointNames_[index];
}

void Skeleton::UpdateInverseBindPose()
{
	uint32_t invBindPoseSize = bindPose_.GetJointSize();
	invBindPose_.resize(invBindPoseSize);

	for (uint32_t index = 0; index < invBindPoseSize; ++index)
	{
		Transform world = bindPose_.GetGlobalTransform(index);
		invBindPose_[index] = Mat4x4::Inverse(Transform::ToMat(world));
	}
}