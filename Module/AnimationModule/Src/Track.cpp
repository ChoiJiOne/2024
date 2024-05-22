#include "Assertion.h"

#include "Track.h"

template Track<float, 1>;
template Track<Vec3f, 3>;
template Track<Quat, 4>;

inline float Interpolation(float a, float b, float t)
{
	return a + (b - a) * t;
}

inline Vec3f Interpolation(const Vec3f& a, const Vec3f& b, float t)
{
	return Vec3f::Lerp(a, b, t);
}

inline Quat Interpolation(const Quat& a, const Quat& b, float t)
{
	Quat result = Quat::Lerp(a, b, t);

	if (Quat::Dot(a, b) < 0.0f)
	{
		result = Quat::Lerp(a, -b, t);
	}

	return Quat::Normalize(result);
}

inline float AdjustHermiteResult(float value)
{
	return value; // nothing...
}

inline Vec3f AdjustHermiteResult(const Vec3f& value)
{
	return value; // nothing...
}

inline Quat AdjustHermiteResult(const Quat& value)
{
	return Quat::Normalize(value);
}

inline void Neighborhood(const float& a, float& b)
{
	// nothing...
}

inline void Neighborhood(const Vec3f& a, Vec3f& b)
{
	// nothing...
}

inline void Neighborhood(const Quat& a, Quat& b)
{
	if (Quat::Dot(a, b) < 0.0f)
	{
		b = -b;
	}
}

template<typename T, uint32_t N>
Keyframe<N>& Track<T, N>::operator[](uint32_t index)
{
	CHECK(0 <= index && index < N);
	return keyframes_[index];
}