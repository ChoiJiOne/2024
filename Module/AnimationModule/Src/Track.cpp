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
