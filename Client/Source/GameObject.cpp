#include "GameObject.h"

bool GameObject::IsCollision(GameObject* object) const
{
	if (this == object) return false; // �ڱ� �ڽŰ��� �浹 ���� X

	const IShape3D* boundingVolume = GetBoundingVolume();
	return boundingVolume->Intersect(object->GetBoundingVolume());
}