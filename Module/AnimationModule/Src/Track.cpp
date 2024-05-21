#include "Assertion.h"
#include "MathModule.h"

#include "Track.h"

inline float Interpolate(float s, float e, float t)
{
	return s + (e - s) * t;
}

inline Vec3f Interpolate(const Vec3f& s, const Vec3f& e, float t)
{
	return Vec3f::Lerp(s, e, t);
}

inline Quat Interpolate(const Quat& s, const Quat& e, float t) 
{
	Quat r = Quat::Lerp(s, e, t);

	if (Quat::Dot(s, e) < 0)
	{
		r = Quat::Lerp(s, -e, t);
	}

	return Quat::Normalize(r);
}

inline float AdjustHermiteResult(float value)
{
	return value;
}

inline Vec3f AdjustHermiteResult(const Vec3f& value)
{
	return value;
}

inline Quat AdjustHermiteResult(const Quat& value)
{
	return Quat::Normalize(value);
}

inline void Neighborhood(const float& a, float& b) 
{
	// Nothing...
}

inline void Neighborhood(const Vec3f& a, Vec3f& b) 
{
	// Nothing...
}

inline void Neighborhood(const Quat& a, Quat& b)
{
	if (Quat::Dot(a, b) < 0.0f)
	{
		b = -b;
	}
}

template Track<float, 1>;
template Track<Vec3f, 3>;
template Track<Quat, 4>;

template<typename T, uint32_t N>
inline Track<T, N>::Track()
{
}

template<typename T, uint32_t N>
Track<T, N>::~Track()
{
}

template<typename T, uint32_t N>
void Track<T, N>::Resize(uint32_t size)
{
	frames_.resize(size);
}

template<typename T, uint32_t N>
float Track<T, N>::GetStartTime() const
{
	return frames_.front().time;
}

template<typename T, uint32_t N>
float Track<T, N>::GetEndTime() const
{
	return frames_.back().time;
}

template<typename T, uint32_t N>
T Track<T, N>::Sample(float time, bool bIsLooping)
{
	T sample;

	switch (interpolation_)
	{
	case EInterpolation::CONSTANT:
		sample = SampleConstant(time, bIsLooping);
		break;

	case EInterpolation::LINEAR:
		sample = SampleLinear(time, bIsLooping);
		break;

	case EInterpolation::CUBIC:
		sample = SampleCubic(time, bIsLooping);
		break;

	default:
		ASSERT(false, "undefined interpolation type");
		break;
	}

	return sample;
}

template<typename T, uint32_t N>
Frame<N>& Track<T, N>::operator[](uint32_t index)
{
	CHECK(0 <= index && index < frames_.size());
	return frames_[index];
}

template<typename T, uint32_t N>
T Track<T, N>::SampleConstant(float time, bool bIsLooping)
{
	int32_t frame = FrameIndex(time, bIsLooping);

	if (frame < 0 || frame >= static_cast<int32_t>(frames_.size()))
	{
		return T();
	}

	return Cast(&frames_[frame].value[0]);
}

template<typename T, uint32_t N>
T Track<T, N>::SampleLinear(float time, bool bIsLooping)
{
	int32_t currFrame = FrameIndex(time, bIsLooping);

	if (currFrame < 0 || currFrame >= static_cast<int32_t>(frames_.size()))
	{
		return T();
	}

	int32_t nextFrame = currFrame + 1;

	float trackTime = AdjustTimeToFitTrack(time, bIsLooping);
	float frameDelta = frames_[nextFrame].time - frames_[currFrame].time;
	if (frameDelta <= 0.0f)
	{
		return T();
	}

	T start = Cast(&frames_[currFrame].value[0]);
	T end = Cast(&frames_[nextFrame].value[0]);
	float t = (trackTime - frames_[currFrame].time) / frameDelta;

	return Interpolate(start, end, t);
}

template<typename T, uint32_t N>
T Track<T, N>::SampleCubic(float time, bool bIsLooping)
{
	int32_t currFrame = FrameIndex(time, bIsLooping);
	if (currFrame < 0 || currFrame >= static_cast<int32_t>(frames_.size()))
	{
		return T();
	}

	int32_t nextFrame = currFrame + 1;

	float trackTime = AdjustTimeToFitTrack(time, bIsLooping);
	float frameDelta = frames_[nextFrame].time - frames_[currFrame].time;
	if (frameDelta <= 0.0f)
	{
		return T();
	}

	float t = (trackTime - frames_[currFrame].time) / frameDelta;

	T point1 = Cast(&frames_[currFrame].value[0]);
	T slope1;
	std::memcpy(&slope1, frames_[currFrame].out, N * sizeof(float));
	slope1 = slope1 * frameDelta;

	T point2 = Cast(&frames_[nextFrame].value[0]);
	T slope2;
	std::memcpy(&slope2, frames_[nextFrame].in, N * sizeof(float));
	slope2 = slope2 * frameDelta;

	return Hermite(t, point1, slope1, point2, slope2);
}

template<typename T, uint32_t N>
T Track<T, N>::Hermite(float time, const T& point1, const T& slope1, const T& point2, const T& slope2)
{
	float t = time;
	float t2 = time * time;
	float t3 = time * time * time;

	T p1 = point1;
	T p2 = point2;
	T s1 = slope1;
	T s2 = slope2;
	Neighborhood(point1, p2);

	float h1 = 2.0f * t3 - 3.0f * t2 + 1.0f;
	float h2 = -2.0f * t3 + 3.0f * t2;
	float h3 = t3 - 2.0f * t2 + t;
	float h4 = t3 - t2;

	T result = p1 * h1 + p2 * h2 + s1 * h3 + s2 * h4;
	return AdjustHermiteResult(result);
}

template<typename T, uint32_t N>
int32_t Track<T, N>::FrameIndex(float time, bool bIsLooping)
{
	uint32_t size = GetSize();

	if (size <= 1)
	{
		return -1;
	}

	if (bIsLooping)
	{
		float startTime = frames_.front().time;
		float endTime = frames_.back().time;
		float duration = endTime - startTime;

		time = MathModule::Fmod(time - startTime, endTime - startTime);

		if (time < 0.0f)
		{
			time += endTime - startTime;
		}

		time += startTime;
	}
	else
	{
		if (time <= frames_.front().time)
		{
			return 0;
		}

		uint32_t index = size - 2;
		if (time >= frames_[index].time)
		{
			return static_cast<int32_t>(index);
		}
	}

	for (int32_t index = size - 1; index >= 0; --index)
	{
		if (time >= frames_[index].time)
		{
			return index;
		}
	}

	return -1;
}

template<typename T, uint32_t N>
float Track<T, N>::AdjustTimeToFitTrack(float time, bool bIsLooping)
{
	uint32_t size = GetSize();

	if (size <= 1)
	{
		return 0.0f;
	}

	float startTime = frames_.front().time;
	float endTime = frames_.back().time;
	float duration = endTime - startTime;

	if (duration <= 0.0f)
	{
		return 0.0f;
	}

	if (bIsLooping)
	{
		time = MathModule::Fmod(time - startTime, endTime - startTime);

		if (time < 0.0f)
		{
			time += endTime - startTime;
		}

		time += startTime;
	}
	else
	{
		if (time <= frames_.front().time)
		{
			time = startTime;
		}

		if (time >= frames_.back().time)
		{
			time = endTime;
		}
	}

	return time;
}

template<>
float Track<float, 1>::Cast(float* value)
{
	return value[0];
}

template<>
Vec3f Track<Vec3f, 3>::Cast(float* value)
{
	return Vec3f(value[0], value[1], value[2]);
}

template<>
Quat Track<Quat, 4>::Cast(float* value)
{
	Quat r = Quat(value[0], value[1], value[2], value[3]);
	return Quat::Normalize(r);
}