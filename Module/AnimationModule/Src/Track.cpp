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

template<typename T, uint32_t N>
Keyframe<N>& Track<T, N>::operator[](uint32_t index)
{
	CHECK(0 <= index && index < N);
	return keyframes_[index];
}