#include "Pose.h"

bool Pose::operator==(Pose&& instance) noexcept
{
	if (joints_.size() != instance.joints_.size())
	{
		return false;
	}

	if (parents_.size() != instance.parents_.size())
	{
		return false;
	}

	uint32_t size = static_cast<uint32_t>(joints_.size());
	for (uint32_t index = 0; index < size; ++index)
	{
		int32_t thisParent = parents_[index];
		int32_t otherParent = instance.parents_[index];
		if (thisParent != otherParent)
		{
			return false;
		}

		Transform thisLocal = joints_[index];
		Transform otherLocal = instance.joints_[index];
		if (thisLocal != otherLocal)
		{
			return false;
		}
	}

	return true;
}

bool Pose::operator==(const Pose& instance)
{
	if (joints_.size() != instance.joints_.size())
	{
		return false;
	}

	if (parents_.size() != instance.parents_.size())
	{
		return false;
	}

	uint32_t size = static_cast<uint32_t>(joints_.size());
	for (uint32_t index = 0; index < size; ++index)
	{
		int32_t thisParent = parents_[index];
		int32_t otherParent = instance.parents_[index];
		if (thisParent != otherParent)
		{
			return false;
		}

		Transform thisLocal = joints_[index];
		Transform otherLocal = instance.joints_[index];
		if (thisLocal != otherLocal)
		{
			return false;
		}
	}

	return true;
}

void Pose::Resize(uint32_t size)
{
	parents_.resize(size);
	joints_.resize(size);
}
