#include "BoundingBox3D.h"
#include "BoundingSphere3D.h"
#include "MathModule.h"

bool BoundingBox3D::Intersect(const IBoundingVolume* boundingVolume) const
{
	bool bIntersect = false;
	EType type = boundingVolume->GetType();

	switch (type)
	{
	case IBoundingVolume::EType::BOX:
		bIntersect = IntersectBoundingBox3D(boundingVolume);
		break;

	case IBoundingVolume::EType::SPHERE:
		bIntersect = IntersectBoundingSphere3D(boundingVolume);
		break;

	default:
		bIntersect = false;
		break;
	}

	return bIntersect;
}

bool BoundingBox3D::IntersectBoundingBox3D(const IBoundingVolume* boundingVolume) const
{
	const BoundingBox3D* box = reinterpret_cast<const BoundingBox3D*>(boundingVolume);

	Vec3f minPos = GetMinPosition();
	Vec3f maxPos = GetMaxPosition();
	Vec3f otherMinPos = box->GetMinPosition();
	Vec3f otherMaxPos = box->GetMaxPosition();

	if (minPos.x > otherMaxPos.x || maxPos.x < otherMinPos.x)
	{
		return false;
	}

	if (minPos.y > otherMaxPos.y || maxPos.y < otherMinPos.y)
	{
		return false;
	}

	if (minPos.z > otherMaxPos.z || maxPos.z < otherMinPos.z)
	{
		return false;
	}

	return true;
}

bool BoundingBox3D::IntersectBoundingSphere3D(const IBoundingVolume* boundingVolume) const
{
	const BoundingSphere3D* sphere = reinterpret_cast<const BoundingSphere3D*>(boundingVolume);
	Vec3f center = sphere->GetCenter();

	Vec3f minPos = GetMinPosition();
	Vec3f maxPos = GetMaxPosition();

	Vec3f closest(
		MathModule::Clamp<float>(center.x, minPos.x, maxPos.x),
		MathModule::Clamp<float>(center.y, minPos.y, maxPos.y),
		MathModule::Clamp<float>(center.z, minPos.z, maxPos.z)
	);

	float distSquare = Vec3f::LengthSq(center - closest);
	float radiusSquare = sphere->GetRadius() * sphere->GetRadius();

	return distSquare <= radiusSquare;
}
