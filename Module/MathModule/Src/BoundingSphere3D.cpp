#include "BoundingBox3D.h"
#include "BoundingSphere3D.h"
#include "MathModule.h"

bool BoundingSphere3D::Intersect(const IBoundingVolume* boundingVolume) const
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

bool BoundingSphere3D::IntersectBoundingBox3D(const IBoundingVolume* boundingVolume) const
{
	const BoundingBox3D* box = reinterpret_cast<const BoundingBox3D*>(boundingVolume);

	Vec3f minPos = box->GetMinPosition();
	Vec3f maxPos = box->GetMaxPosition();

	Vec3f closest(
		MathModule::Clamp<float>(center_.x, minPos.x, maxPos.x),
		MathModule::Clamp<float>(center_.y, minPos.y, maxPos.y),
		MathModule::Clamp<float>(center_.z, minPos.z, maxPos.z)
	);

	float distSquare = Vec3f::LengthSq(center_ - closest);
	float radiusSquare = radius_ * radius_;

	return distSquare <= radiusSquare;
}

bool BoundingSphere3D::IntersectBoundingSphere3D(const IBoundingVolume* boundingVolume) const
{
	const BoundingSphere3D* sphere = reinterpret_cast<const BoundingSphere3D*>(boundingVolume);

	float lengthSq = Vec3f::LengthSq(center_ - sphere->GetCenter());
	float sumRadius = (radius_ + sphere->GetRadius());

	return lengthSq <= (sumRadius * sumRadius);
}