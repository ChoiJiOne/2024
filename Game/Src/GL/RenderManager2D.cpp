#pragma warning(push)
#pragma warning(disable: 26495)
#pragma warning(disable: 26819)
#pragma warning(disable: 26451)
#pragma warning(disable: 6031)

#include <glad/glad.h>

#include "Entity/Camera2D.h"
#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/Shader.h"
#include "GL/UniformBuffer.h"
#include "GL/VertexBuffer.h"
#include "Utils/Assertion.h"

RenderManager2D RenderManager2D::singleton_;

RenderManager2D& RenderManager2D::GetRef()
{
	return singleton_;
}

RenderManager2D* RenderManager2D::GetPtr()
{
	return &singleton_;
}

void RenderManager2D::Startup()
{
	glManager_ = GLManager::GetPtr();
}

void RenderManager2D::Shutdown()
{
	glManager_ = nullptr;
}

#pragma warning(pop)