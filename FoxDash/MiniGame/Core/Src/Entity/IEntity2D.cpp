#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"

IEntity2D::IEntity2D()
{
	renderManager_ = RenderManager2D::GetPtr();
}

IEntity2D::~IEntity2D()
{
	renderManager_ = nullptr;
}
