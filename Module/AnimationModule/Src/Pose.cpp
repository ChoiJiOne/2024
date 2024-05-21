#include "Assertion.h"

#include "Pose.h"

Pose::Pose(uint32_t size)
{
	Resize(size);
}

Pose::Pose(Pose&& instance) noexcept
	: joints_(instance.joints_)
	, parents_(instance.parents_)
{}

Pose::Pose(const Pose& instance) noexcept
	: joints_(instance.joints_)
	, parents_(instance.parents_)
{}

Pose& Pose::operator=(Pose&& instance) noexcept
{
	if (this == &instance) return *this;

	parents_ = instance.parents_;
	joints_ = instance.joints_;

	return *this;
}

Pose& Pose::operator=(const Pose& instance) noexcept
{
	if (this == &instance) return *this;

	parents_ = instance.parents_;
	joints_ = instance.joints_;

	return *this;
}

bool Pose::operator==(Pose&& instance) noexcept
{
	if (joints_.size() != instance.joints_.size() || parents_.size() != instance.parents_.size())
	{
		return false;
	}

	uint32_t size = static_cast<uint32_t>(joints_.size());
	for (uint32_t index = 0; index < size; ++index)
	{
		Transform thisLocal = joints_[index];
		Transform otherLocal = instance.joints_[index];

		int32_t thisParent = parents_[index];
		int32_t otherParent = instance.parents_[index];

		if (thisParent != otherParent)
		{
			return false;
		}

		if (thisLocal != otherLocal)
		{
			return false;
		}
	}

	return true;
}

bool Pose::operator==(const Pose& instance) noexcept
{
	if (joints_.size() != instance.joints_.size() || parents_.size() != instance.parents_.size())
	{
		return false;
	}

	uint32_t size = static_cast<uint32_t>(joints_.size());
	for (uint32_t index = 0; index < size; ++index)
	{
		Transform thisLocal = joints_[index];
		Transform otherLocal = instance.joints_[index];

		int32_t thisParent = parents_[index];
		int32_t otherParent = instance.parents_[index];

		if (thisParent != otherParent)
		{
			return false;
		}

		if (thisLocal != otherLocal)
		{
			return false;
		}
	}

	return true;
}

bool Pose::operator!=(Pose&& instance) noexcept
{
	return !(*this == instance);
}

bool Pose::operator!=(const Pose& instance) noexcept
{
	return !(*this == instance);
}

Transform Pose::operator[](uint32_t index)
{
	return GetGlobalTransform(index);
}

void Pose::Resize(uint32_t size)
{
	parents_.resize(size);
	joints_.resize(size);
}

Transform Pose::GetLocalTransform(uint32_t index)
{
	CHECK(0 <= index && index < joints_.size());
	return joints_[index];
}

void Pose::SetLocalTransform(uint32_t index, const Transform& transform)
{
	CHECK(0 <= index && index < joints_.size());
	joints_[index] = transform;
}

Transform Pose::GetGlobalTransform(uint32_t index)
{
	CHECK(0 <= index && index < joints_.size());

	Transform result = joints_[index];
	for (int32_t parent = parents_[index]; parent >= 0; parent = parents_[parent])
	{
		result = Transform::Combine(joints_[parent], result);
	}

	return result;
}

void Pose::GetMatrixPalette(std::vector<Mat4x4>& outMatrices)
{
	uint32_t size = GetJointSize();
	if (outMatrices.size() != size)
	{
		outMatrices.resize(size);
	}

	for (uint32_t index = 0; index < size; ++index)
	{
		Transform t = GetGlobalTransform(index);
		outMatrices[index] = Transform::ToMat(t);
	}
}

int32_t Pose::GetParent(uint32_t index)
{
	return parents_[index];
}

void Pose::SetParent(uint32_t index, int32_t parent)
{
	parents_[index] = parent;
}