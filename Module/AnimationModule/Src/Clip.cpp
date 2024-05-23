#include "Assertion.h"

#include "Clip.h"

uint32_t Clip::GetBoneID(uint32_t index)
{
	CHECK(0 <= index && index < tracks_.size());
	return tracks_[index].GetBoneID();
}

void Clip::SetBoneID(uint32_t index, uint32_t boneID)
{
	CHECK(0 <= index && index < tracks_.size());
	tracks_[index].SetBoneID(boneID);
}

TransformTrack& Clip::operator[](uint32_t boneID)
{
	uint32_t size = static_cast<uint32_t>(tracks_.size());

	for (uint32_t index = 0; index < size; ++index)
	{
		if (tracks_[index].GetBoneID() == boneID)
		{
			return tracks_[index];
		}
	}

	tracks_.push_back(TransformTrack());
	tracks_.back().SetBoneID(boneID);
	return tracks_.back();
}
