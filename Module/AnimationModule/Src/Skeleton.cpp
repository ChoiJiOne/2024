#include "Skeleton.h"

void Skeleton::UpdateInverseBindPose()
{
	uint32_t size = bindPose_.Size();
	invBindPose_.resize(size);

	for (uint32_t index = 0; index < size; ++index)
	{
		Transform world = bindPose_.GetGlobalTransform(index);
		invBindPose_[index] = Mat4x4::Inverse(Transform::ToMat(world));
	}
}
