#include "Physic/OrientedRect2D.h"

bool OrientedRect2D::Intersect(const ICollider2D* collider) const
{
	return false;
}

void OrientedRect2D::GetInterval(const glm::vec2& axis, float& outMin, float& outMax) const
{
}
