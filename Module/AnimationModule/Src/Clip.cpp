#include "Assertion.h"

#include "Clip.h"

uint32_t Clip::GetTrackID(uint32_t index)
{
	CHECK(0 <= index && index < tracks_.size());
	return tracks_[index].GetBoneID();
}

void Clip::SetTrackID(uint32_t index, uint32_t id)
{
	CHECK(0 <= index && index < tracks_.size());
	tracks_[index].SetBoneID(id);
}

float Clip::Sample(Pose& outPose, float time)
{
	if (GetDuration() == 0.0f)
	{
		return 0.0f;
	}

	time = AdjustTimeToFitRange(time);

	for (uint32_t index = 0; index < tracks_.size(); ++index)
	{
		uint32_t joint = tracks_[index].GetBoneID();

		Transform local = outPose.GetLocalTransform(joint);
		Transform animated = tracks_[index].Sample(local, time, bIsLooping_);

		outPose.SetLocalTransform(joint, animated);
	}

	return time;
}

TransformTrack& Clip::operator[](uint32_t index)
{
	uint32_t trackSize = GetTrackSize();

	for (uint32_t i = 0; i < trackSize; ++i)
	{
		if (tracks_[i].GetBoneID() == index)
		{
			return tracks_[i];
		}
	}

	tracks_.push_back(TransformTrack());
	tracks_.back().SetBoneID(index);

	return tracks_.back();
}

void Clip::RecomputeDuration()
{
	startTime_ = 0.0f;
	endTime_ = 0.0f;
	bool startSet = false;
	bool endSet = false;

	uint32_t trackSize = GetTrackSize();
	for (uint32_t index = 0; index < trackSize; ++index)
	{
		if (tracks_[index].IsValid())
		{
			float trackStartTime = tracks_[index].GetStartTime();
			float trackEndTime = tracks_[index].GetEndTime();

			if (trackStartTime < startTime_ || !startSet)
			{
				startTime_ = trackStartTime;
				startSet = true;
			}

			if (trackEndTime > endTime_ || !endSet) {
				endTime_ = trackEndTime;
				endSet = true;
			}
		}
	}
}

float Clip::AdjustTimeToFitRange(float time)
{
	if (bIsLooping_)
	{
		float duration = endTime_ - startTime_;
		if (duration <= 0.0f)
		{
			return 0.0f;
		}

		time = MathModule::Fmod(time - startTime_, endTime_ - startTime_);
		if (time < 0.0f)
		{
			time += endTime_ - startTime_;
		}

		time += startTime_;
	}
	else
	{
		if (time < startTime_)
		{
			time = startTime_;
		}

		if (time > endTime_)
		{
			time = endTime_;
		}
	}
	return time;
}