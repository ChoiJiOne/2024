#include "TransformTrack.h"

float TransformTrack::GetStartTime()
{
	float result = 0.0f;
	bool bIsSet = false;

	if (position_.GetSize() > 1)
	{
		result = position_.GetStartTime();
		bIsSet = true;
	}

	if (rotate_.GetSize() > 1)
	{
		float rotateStart = rotate_.GetStartTime();
		if (rotateStart < result || !bIsSet)
		{
			result = rotateStart;
			bIsSet = true;
		}
	}

	if (scale_.GetSize() > 1)
	{
		float scaleStart = scale_.GetStartTime();
		if (scaleStart < result || !bIsSet)
		{
			result = scaleStart;
			bIsSet = true;
		}
	}

	return result;
}

float TransformTrack::GetEndTime()
{
	float result = 0.0f;
	bool bIsSet = false;

	if (position_.GetSize() > 1)
	{
		result = position_.GetEndTime();
		bIsSet = true;
	}

	if (rotate_.GetSize() > 1)
	{
		float rotateEnd = rotate_.GetEndTime();
		if (rotateEnd > result || !bIsSet)
		{
			result = rotateEnd;
			bIsSet = true;
		}
	}

	if (scale_.GetSize() > 1)
	{
		float scaleEnd = scale_.GetEndTime();
		if (scaleEnd > result || !bIsSet)
		{
			result = scaleEnd;
			bIsSet = true;
		}
	}

	return result;
}

bool TransformTrack::IsValid()
{
	return position_.GetSize() > 1 || rotate_.GetSize() > 1 || scale_.GetSize() > 1;
}

Transform TransformTrack::Sample(const Transform& transform, float time, bool bIsLooping)
{
	Transform result = transform;

	if (position_.GetSize() > 1)
	{
		result.position = position_.Sample(time, bIsLooping);
	}

	if (rotate_.GetSize() > 1)
	{
		result.rotate = rotate_.Sample(time, bIsLooping);
	}

	if (scale_.GetSize() > 1)
	{
		result.scale = scale_.Sample(time, bIsLooping);
	}

	return result;
}