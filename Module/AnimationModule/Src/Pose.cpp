#include "Pose.h"

void Pose::Resize(uint32_t size)
{
	parents_.resize(size);
	joints_.resize(size);
}
