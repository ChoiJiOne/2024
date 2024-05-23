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
