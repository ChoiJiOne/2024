#include "Assertion.h"

#include "Track.h"

template Track<float, 1>;
template Track<Vec3f, 3>;
template Track<Quat, 4>;

template<typename T, uint32_t N>
Keyframe<N>& Track<T, N>::operator[](uint32_t index)
{
	CHECK(0 <= index && index < N);
	return keyframes_[index];
}